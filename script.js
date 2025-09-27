// script.js
// Implements the five ciphers in the web UI

function sanitizeAlpha(s) {
  return s.split('').filter(c => /[A-Za-z]/.test(c)).map(c => c.toUpperCase()).join('');
}

function caesarEncryptText(text, k) {
  return text.split('').map(ch => {
    if (/[A-Za-z]/.test(ch)) {
      const base = (ch === ch.toUpperCase()) ? 'A'.charCodeAt(0) : 'a'.charCodeAt(0);
      const code = ch.charCodeAt(0);
      return String.fromCharCode(base + ( (code - base + k + 26) % 26 ));
    } else return ch;
  }).join('');
}
function caesarDecryptText(text, k) { return caesarEncryptText(text, -k); }

// Affine
function gcd(a,b){ return b===0?Math.abs(a):gcd(b,a%b); }
function invMod(a, m) {
  a = ((a % m) + m) % m;
  for (let x=0;x<m;x++) if ((a*x) % m === 1) return x;
  return null;
}
function affineEncrypt(text, a, b) {
  text = sanitizeAlpha(text);
  if (gcd(a,26) !== 1) return "Error: a not coprime with 26";
  return text.split('').map(ch => {
    const p = ch.charCodeAt(0) - 65;
    return String.fromCharCode(65 + ((a*p + b) % 26));
  }).join('');
}
function affineDecrypt(text, a, b) {
  text = sanitizeAlpha(text);
  const ainv = invMod(a,26);
  if (ainv === null) return "Error: a not coprime with 26";
  return text.split('').map(ch => {
    const c = ch.charCodeAt(0) - 65;
    return String.fromCharCode(65 + ((ainv*(c - b + 26)) % 26));
  }).join('');
}

// Columnar Transposition (Permutation by key string)
function keyOrderFromString(key) {
  key = key.split('');
  const arr = key.map((ch,i) => ({ch: ch.toUpperCase(), i}));
  arr.sort((a,b) => a.ch.localeCompare(b.ch) || a.i - b.i);
  const order = new Array(key.length);
  arr.forEach((item, rank) => { order[item.i] = rank; });
  return order;
}
function columnarEncrypt(text, key) {
  let s = sanitizeAlpha(text);
  const cols = key.length;
  if (cols === 0) return "";
  const rows = Math.ceil(s.length/cols);
  while (s.length < rows*cols) s += 'X';
  const table = [];
  let p = 0;
  for (let r=0;r<rows;r++){
    table[r] = [];
    for (let c=0;c<cols;c++) table[r][c] = s[p++];
  }
  const order = keyOrderFromString(key);
  let out = '';
  for (let rank=0; rank<cols; rank++){
    for (let c=0;c<cols;c++) if (order[c]===rank) {
      for (let r=0;r<rows;r++) out += table[r][c];
      break;
    }
  }
  return out;
}
function columnarDecrypt(text, key) {
  let s = sanitizeAlpha(text);
  const cols = key.length;
  if (cols === 0) return "";
  const rows = Math.ceil(s.length/cols);
  const table = Array.from({length:rows}, ()=>Array(cols).fill('X'));
  const order = keyOrderFromString(key);
  let p = 0;
  for (let rank=0; rank<cols; rank++){
    for (let c=0;c<cols;c++) if (order[c]===rank) {
      for (let r=0;r<rows;r++) {
        table[r][c] = (p < s.length) ? s[p++] : 'X';
      }
      break;
    }
  }
  let out = '';
  for (let r=0;r<rows;r++) for (let c=0;c<cols;c++) out += table[r][c];
  return out;
}

// Vigenere
function vigenereEncrypt(text, key) {
  const p = sanitizeAlpha(text);
  const k = sanitizeAlpha(key);
  if (k.length === 0) return "(empty key)";
  let out = '';
  for (let i=0;i<p.length;i++){
    const pi = p.charCodeAt(i)-65;
    const ki = k.charCodeAt(i % k.length)-65;
    out += String.fromCharCode(65 + ((pi + ki) % 26));
  }
  return out;
}
function vigenereDecrypt(text, key) {
  const c = sanitizeAlpha(text);
  const k = sanitizeAlpha(key);
  if (k.length === 0) return "(empty key)";
  let out = '';
  for (let i=0;i<c.length;i++){
    const ci = c.charCodeAt(i)-65;
    const ki = k.charCodeAt(i % k.length)-65;
    out += String.fromCharCode(65 + ((ci - ki + 26) % 26));
  }
  return out;
}

// Playfair
function makePlayfairTable(key) {
  const used = {};
  let s = "";
  const addChar = ch => {
    if (ch === 'J') ch = 'I';
    if (!used[ch]) { used[ch]=true; s += ch; }
  };
  const k = sanitizeAlpha(key);
  for (const ch of k) addChar(ch);
  for (let code=65; code<=90; ++code) {
    const ch = String.fromCharCode(code);
    if (ch === 'J') continue;
    addChar(ch);
  }
  const table = [];
  const pos = {};
  let p = 0;
  for (let r=0;r<5;r++){
    table[r] = [];
    for (let c=0;c<5;c++){
      const ch = s[p++];
      table[r][c] = ch;
      pos[ch] = {r,c};
    }
  }
  return {table,pos};
}
function playfairPairs(plain) {
  let s = sanitizeAlpha(plain).replace(/J/g,'I');
  const pairs = [];
  for (let i=0;i<s.length;) {
    const a = s[i];
    const b = (i+1 < s.length) ? s[i+1] : null;
    if (b === null) { pairs.push([a,'X']); i++; }
    else if (a === b) { pairs.push([a,'X']); i++; }
    else { pairs.push([a,b]); i += 2; }
  }
  return pairs;
}
function playfairEncrypt(plain, key) {
  const {table,pos} = makePlayfairTable(key);
  const pairs = playfairPairs(plain);
  let out = '';
  for (const [A,B] of pairs) {
    const pa = pos[A], pb = pos[B];
    if (pa.r === pb.r) {
      out += table[pa.r][(pa.c+1)%5];
      out += table[pb.r][(pb.c+1)%5];
    } else if (pa.c === pb.c) {
      out += table[(pa.r+1)%5][pa.c];
      out += table[(pb.r+1)%5][pb.c];
    } else {
      out += table[pa.r][pb.c];
      out += table[pb.r][pa.c];
    }
  }
  return out;
}
function playfairDecrypt(cipher, key) {
  const {table,pos} = makePlayfairTable(key);
  const s = sanitizeAlpha(cipher);
  let out = '';
  for (let i=0;i+1<s.length;i+=2) {
    const A = s[i], B = s[i+1];
    const pa = pos[A], pb = pos[B];
    if (pa.r === pb.r) {
      out += table[pa.r][(pa.c+4)%5];
      out += table[pb.r][(pb.c+4)%5];
    } else if (pa.c === pb.c) {
      out += table[(pa.r+4)%5][pa.c];
      out += table[(pb.r+4)%5][pb.c];
    } else {
      out += table[pa.r][pb.c];
      out += table[pb.r][pa.c];
    }
  }
  return out;
}

// UI Wireup
document.addEventListener('DOMContentLoaded', () => {
  const cipherSelect = document.getElementById('cipher');
  const modeSelect = document.getElementById('mode');
  const textArea = document.getElementById('text');
  const keyInput = document.getElementById('key');
  const outputArea = document.getElementById('output');
  const runBtn = document.getElementById('run');
  const clearBtn = document.getElementById('clear');
  const affineParams = document.getElementById('affine-params');
  const aInput = document.getElementById('a');
  const bInput = document.getElementById('b');

  function updateKeyUI() {
    const sel = cipherSelect.value;
    if (sel === 'affine') {
      affineParams.classList.remove('hidden');
      keyInput.parentElement.style.display = 'none';
    } else if (sel === 'perm') {
      affineParams.classList.add('hidden');
      keyInput.parentElement.style.display = 'block';
      keyInput.placeholder = 'Ví dụ: ZEBRAS hoặc 3142';
    } else {
      affineParams.classList.add('hidden');
      keyInput.parentElement.style.display = 'block';
      keyInput.placeholder = '';
    }
  }
  cipherSelect.addEventListener('change', updateKeyUI);
  updateKeyUI();

  runBtn.addEventListener('click', () => {
    const cipher = cipherSelect.value;
    const mode = modeSelect.value;
    const text = textArea.value;
    const key = keyInput.value;
    let res = '';
    try {
      if (cipher === 'caesar') {
        const k = parseInt(key) || 3;
        res = (mode === 'encrypt') ? caesarEncryptText(text, k) : caesarDecryptText(text, k);
      } else if (cipher === 'affine') {
        const a = parseInt(aInput.value) || 5;
        const b = parseInt(bInput.value) || 8;
        if (mode === 'encrypt') res = affineEncrypt(text, a, b);
        else res = affineDecrypt(text, a, b);
      } else if (cipher === 'perm') {
        if (!key) { res = "Require key for permutation (string)"; }
        else {
          res = (mode === 'encrypt') ? columnarEncrypt(text, key) : columnarDecrypt(text, key);
        }
      } else if (cipher === 'vigenere') {
        if (!key) res = "Require key for Vigenere";
        else res = (mode === 'encrypt') ? vigenereEncrypt(text, key) : vigenereDecrypt(text, key);
      } else if (cipher === 'playfair') {
        if (!key) res = "Require key for Playfair";
        else res = (mode === 'encrypt') ? playfairEncrypt(text, key) : playfairDecrypt(text, key);
      }
    } catch (e) {
      res = "Error: " + (e.message || e);
    }
    outputArea.value = res;
  });

  clearBtn.addEventListener('click', () => {
    textArea.value = '';
    outputArea.value = '';
  });
});
