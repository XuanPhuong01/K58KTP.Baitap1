# K58KTP.Baitap1
# *K225480106054_Nguyễn Thị Xuân Phương*
# TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
- 1.Caesar
- 2.Affine
- 3.Hoán vị
- 4.Vigenère
- 5.Playfair
# Với mỗi phương pháp, hãy tìm hiểu:
- Tên gọi
- Thuật toán mã hoá, thuật toán giải mã
- Không gian khóa
- Cách phá mã (mà không cần khoá)
- Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript
# BÀI LÀM
## 1.Caesar
### Tên gọi
+ Caesar Cipher, hay Mã hóa dịch chữ cái theo bảng chữ cái.
### Thuật toán
+ Mã Hóa:
+ Dịch mỗi ký tự X trong bản rõ P theo công thức
+         C= (x+k) mod 26
+ Giải mã:
+         P = (C-k +36) mod 26
+ Trong đó k là khóa ( số nguyên từ 0 đến 25), x và c là vị trí chữ cái trong bảng A-Z (0-25)
### Không gian khóa:
+ 26 khả năng (k=0 đến 25)
### Cách phá mã ( không cần khóa):
+ Tấn công Brute-force: Thử tất cả 26 khả năng.
+ Tấn công tần suất: So sánh tần suất chữ cái trong bản mã với tần suất chữ cái phổ biến trong tiếng Anh( E,T,A..)
## Kết quả 
+ C++
  <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/844f1462-f727-4984-bd1f-3e1fb75882cc" />
  
+ Html
  <img width="1015" height="873" alt="image" src="https://github.com/user-attachments/assets/1df65cbe-16b1-46e2-8efa-3ed140c1ff7f" />
  <img width="1020" height="888" alt="image" src="https://github.com/user-attachments/assets/802da5b6-7434-4c63-b3d5-c982ef702a04" />

## 2.Affine
### Tên Gọi
 + Affine Cipher: kết hợp phép nhân và cộng modulo 26.
### Thuật toán
 + Mã hóa: C = (a*P + b) mod 26
 + Giải mã: P = a^-1 * (C - b) mod 26 (a^-1 là nghịch đảo modulo 26)
 + a và 26 phải nguyên tố cùng nhau.
### Không gian khóa
 + 12x26 =312 khóa (12 khả năng cho a,26 khả năng cho b)
### Cách phá mã: 
 + Brute-force 312 khóa
 + Phân tích tần suất
### Kết Quả
 + C++
   <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/7bd3a82c-45c6-4aca-9e19-362944535c62" />
   <img width="1920" height="1080" alt="Ảnh chụp màn hình (981)" src="https://github.com/user-attachments/assets/6066c32c-ca38-464b-8296-ac7af738c07e" />

 + HTML
   <img width="1034" height="879" alt="image" src="https://github.com/user-attachments/assets/f0474015-8f11-4c57-9833-ac0f95b428ad" />
   <img width="1028" height="874" alt="image" src="https://github.com/user-attachments/assets/2055eb08-4f10-437b-8e92-75c13100e911" />

## 3.Hoán vị
### Tên gọi
 + Mã hóa hoán vị sắp xếp lại vị trí các ký tự trong bản rõ theo một quy tắc nhất định
### Thuật toán
 + Mã hoá: Chia bản rõ thành các khối dài n ký tự, sau đó hoán vị theo khóa k (một dãy số xác định vị trí ký tự).
Ví dụ khóa k=[3,1,2], bản rõ "ABCDEF" → chia thành "ABC" "DEF" → hoán vị theo khóa "CAB" "FDE" → kết quả "CABFDE".
 + Giải mã: Dùng cùng khóa k đảo lại vị trí ký tự.
### Không gian khóa:
 + Mọi hoán vị của n ký tự: n! khả năng.
 + Ví dụ n=4 → 4! = 24 khả năng.
### Cách phá mã:
 + Brute force: thử tất cả hoán vị (chỉ khả thi với n nhỏ)
 + Phân tích mẫu: dựa trên cấu trúc ngôn ngữ, các nhóm ký tự phổ biến.
### Kết Quả
 + C++
   <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/8ef02a34-4ad3-477e-9b35-ef1145bda6ad" />
 + HTML
   <img width="1010" height="910" alt="image" src="https://github.com/user-attachments/assets/de5a0f80-8458-49fc-825b-7967967d82fb" />
   <img width="1015" height="911" alt="image" src="https://github.com/user-attachments/assets/ca17b890-e4be-47dc-a77c-f4565a82f812" />

## 4.Vigenère
### Tên gọi
 + Vigenère Cipher là phương pháp dùng chuỗi khóa lặp lại để dịch chuyển chữ cái, còn gọi là “mã hoá chữ cái đa dạng”.
### Thuật toán
 + Mã hóa:
 +       Ci​=(Pi​+Ki​)mod26
 + P_i: ký tự bản rõ
 + K_i: ký tự khóa (A=0, B=1,…)
 + C_i: ký tự mã hoá
 + Giải mã
 +       Pi​=(Ci​−Ki​+26)mod26
### Không gian khóa:
+ Khóa là chuỗi ký tự, độ dài tùy ý → không gian khóa rất lớn.
### Cách phá mã:
+ Kasiski Test hoặc Friedman Test để tìm độ dài khóa
+ Sau đó phân tích tần suất từng nhóm ký tự.
### Kết Quả
+ C++
  <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/87ef153e-dfba-461c-b2e6-a02ac3294b39" />
+ HTML
  <img width="1025" height="913" alt="image" src="https://github.com/user-attachments/assets/44499e52-fdb9-48dd-a29b-4e17d74a19b6" />
  <img width="1017" height="900" alt="image" src="https://github.com/user-attachments/assets/823e0c88-8ccd-48f0-9915-e714b2dcd1f8" />

## 5.PlayFair
### Tên gọi
  + Được phát triển bởi Charles Wheatstone (1854) nhưng được Playfair quảng bá, dùng bảng 5x5 mã hoá cặp ký tự.
### Thuần toán
  + Mã hóa:
    + Tạo bảng 5x5 từ khóa (chữ I/J ghép chung)
    + Chia bản rõ thành cặp ký tự (digraph), thêm ký tự filler nếu cần
    + Mã hoá theo 3 quy tắc: cùng hàng, cùng cột, chữ nhật
  + Giải mã: Áp dụng ngược lại các quy tắc
### Không gian khóa
  + 25! khả năng sắp xếp bảng (tuy nhiên thực tế là nhỏ hơn do ràng buộc)
### Cách phá mã:
  + Phân tích digraph: dựa vào tần suất các cặp chữ cái.
## Kết Quả
 + C++
   <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/f842a53f-9249-4774-ae59-19cc83783f2d" />
 + HTML
   <img width="1025" height="882" alt="image" src="https://github.com/user-attachments/assets/8541941d-5062-4943-b9b5-767478705707" />
   <img width="1030" height="917" alt="image" src="https://github.com/user-attachments/assets/9eeb980a-c280-4140-8a48-15794c35c79a" />






 
