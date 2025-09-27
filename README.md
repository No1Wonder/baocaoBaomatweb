## TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
Caesar  
Affine  
Hoán vị  
Vigenère  
Playfair  
## Với mỗi phương pháp, hãy tìm hiểu:  
Tên gọi  
Thuật toán mã hoá, thuật toán giải mã  
Không gian khóa  
Cách phá mã (mà không cần khoá)  
# 1. Caesar (Shift Cipher)
 Tên: Caesar cipher  
 Thuật toán mã hoá / giải mã (A=0..25):  
 Mã hoá: C = (P + k) mod 26  
 Giải mã: P = (C - k) mod 26  
 Không gian khoá: 26 khả năng (25 hữu hiệu).  
 Cách phá: brute-force 25 khoá hoặc phân tích tần suất.  
<img width="990" height="496" alt="image" src="https://github.com/user-attachments/assets/06ac2437-03b9-42b8-95c6-3beb154a1f12" />
<img width="989" height="493" alt="image" src="https://github.com/user-attachments/assets/13c7d5e7-b653-4b83-9b6f-2493a278af0f" />
# 2. Affine Cipher
 Tên: Affine cipher  
 Thuật toán:  
 Mã hoá: C = (a * P + b) mod 26 với gcd(a,26)=1  
 Giải mã: P = a^(-1) * (C - b) mod 26  
 Không gian khoá: 12 * 26 = 312 khả năng.  
 Cách phá: brute-force, phân tích tần suất, known-plaintext.  
<img width="990" height="496" alt="image" src="https://github.com/user-attachments/assets/30d087a0-74ab-4696-91ed-5292c6276bd0" />
<img width="979" height="488" alt="image" src="https://github.com/user-attachments/assets/3bdf04f8-1a87-4d4b-a66c-d08ec0e72559" />
# 3. Hoán vị (Permutation / Transposition)
 Tên: Transposition cipher (ví dụ: Columnar).  
 Thuật toán:  
 Viết plaintext vào bảng n cột.  
 Hoán vị cột theo khoá (một permutation).  
 Đọc ciphertext theo cột.  
 Không gian khoá: n! (n là số cột).  
 Cách phá: thử permutation nhỏ, phân tích mẫu lặp, heuristic search.  
 <img width="990" height="492" alt="image" src="https://github.com/user-attachments/assets/3b0d39a4-1792-4108-9a2b-0fc550d3c57e" />
<img width="989" height="485" alt="image" src="https://github.com/user-attachments/assets/d35c4506-0b08-4916-a37d-dd8e410b4e25" />
# 4. Vigenère Cipher
 Tên: Vigenère cipher (polyalphabetic).  
 Thuật toán:  
 Mã hoá: C[i] = (P[i] + K[i mod m]) mod 26  
 Giải mã: P[i] = (C[i] - K[i mod m]) mod 26  
 Không gian khoá: 26^m với khoá dài m.  
 Cách phá: Kasiski test, Friedman test (IC), sau đó phân tích tần suất từng Caesar.  
<img width="988" height="491" alt="image" src="https://github.com/user-attachments/assets/7a46cb40-2c1a-4f27-8221-852d3767568d" />
<img width="988" height="495" alt="image" src="https://github.com/user-attachments/assets/d47d3fb1-3956-4b1e-9344-d3a18599b362" />

# 5. Playfair Cipher
Tên: Playfair cipher (digraph substitution).  
Thuật toán:  
Tạo bảng 5x5 từ từ khoá (25 chữ).  
Chia plaintext thành cặp ký tự.  
Quy tắc mã hoá:  
Cùng hàng → lấy chữ bên phải.  
Cùng cột → lấy chữ bên dưới.  
Hình chữ nhật → lấy chữ cùng hàng, cột của chữ kia.  
Không gian khoá: khoảng 25! (rất lớn, nhưng thực tế nhỏ hơn do tạo từ từ khoá).  
Cách phá: phân tích digraph, brute-force bằng heuristic, known-plaintext.  
<img width="984" height="497" alt="image" src="https://github.com/user-attachments/assets/8aff8890-a3ad-4d2b-a903-9ec77a7ab984" />
<img width="991" height="499" alt="image" src="https://github.com/user-attachments/assets/1550327b-1364-44ab-8690-8a3bd68ea62f" />


