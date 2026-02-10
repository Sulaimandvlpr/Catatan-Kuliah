# Pertemuan 1 — Matriks

## 1. Pengertian Matriks

Matriks adalah susunan bilangan berbentuk persegi panjang yang terdiri dari **baris (row)** dan **kolom (column)**.

Secara umum, matriks berukuran `m x n` berarti:

* Memiliki `m` baris
* Memiliki `n` kolom

Contoh matriks 2×3:

```text
A = | 1  2  3 |
    | 4  5  6 |
```

---

# 2. Macam-Macam Matriks

## 2.1 Matriks Nol (Zero Matrix)

Matriks yang **semua elemennya bernilai 0**.

Contoh:

```text
A = | 0  0 |
    | 0  0 |
```

---

## 2.2 Matriks Identitas (Identity Matrix)

Matriks persegi yang:

* Elemen diagonal utama = 1
* Elemen lainnya = 0

Biasanya dilambangkan dengan `I`.

Contoh matriks identitas 3×3:

```text
I₃ =  | 1  0  0 |
      | 0  1  0 |
      | 0  0  1 |
```

Sifat penting:

```text
A × I = A
I × A = A
```

---

## 2.3 Matriks Diagonal

Matriks persegi yang semua elemen **di luar diagonal utama bernilai 0**.

Bentuk umum:

```text
D = | d₁  0   0  |
    | 0   d₂  0  |
    | 0   0   d₃ |
```

Contoh:

```text
D = | 8  0  0 |
    | 0  4  0 |
    | 0  0  6 |
```

---

## 2.4 Matriks Segitiga

### Matriks Segitiga Bawah

Semua elemen **di atas diagonal utama = 0**

```text
A = | 1  0  0 |
    | 2  3  0 |
    | 4  5  6 |
```

---

### Matriks Segitiga Atas

Semua elemen **di bawah diagonal utama = 0**

```text
A = | 1  2  3 |
    | 0  4  5 |
    | 0  0  6 |
```

---

## 2.5 Matriks Simetris

Matriks persegi yang memenuhi:

```text
A = Aᵀ
```

Artinya: elemen baris dan kolom saling bercermin.

Contoh:

```text
A = | 1  2  3 |
    | 2  4  5 |
    | 3  5  6 |
```

---

# 3. Transpose Matriks

## 3.1 Definisi

Transpose matriks adalah proses **menukar baris menjadi kolom**.

Jika A berukuran `m × n`, maka:

```text
Aᵀ berukuran n × m
```

Contoh:

```text
A = | 1  2  3 |
    | 4  5  6 |

Aᵀ = | 1  4 |
      | 2  5 |
      | 3  6 |
```

---

## 3.2 Sifat-Sifat Transpose

```text
1. (Aᵀ)ᵀ = A
2. (A ± B)ᵀ = Aᵀ ± Bᵀ
3. (AB)ᵀ = BᵀAᵀ
4. (kA)ᵀ = kAᵀ
```

---

# 4. Invers Matriks

## 4.1 Definisi

Matriks A memiliki invers jika terdapat matriks B sehingga:

```text
AB = BA = I
```

Maka:

```text
B = A⁻¹
```

Tidak semua matriks memiliki invers.

---

## 4.2 Invers Matriks 2×2

Jika:

```text
A = | a  b |
    | c  d |
```

Maka invers ada jika:

```text
ad − bc ≠ 0
```

Rumus invers:

```text
A⁻¹ = 1/(ad - bc)  |  d  -b |
                      | -c   a |
```

---

### Contoh Soal

Diketahui:

```text
A = | 2  1 |
    | 5  3 |
```

### Langkah 1: Hitung Determinan

```text
det(A) = (2)(3) - (1)(5)
        = 6 - 5
        = 1
```

### Langkah 2: Gunakan Rumus

```text
A⁻¹ = 1/1 |  3  -1 |
           | -5   2 |
```

Hasil:

```text
A⁻¹ = |  3  -1 |
      | -5   2 |
```

---

## 4.3 Sifat Invers

Jika A dan B memiliki invers:

```text
1. (AB)⁻¹ = B⁻¹A⁻¹
2. (A⁻¹)⁻¹ = A
```

---

# 5. Pangkat Matriks

## 5.1 Definisi

Jika A matriks persegi:

```text
A⁰ = I
A¹ = A
A² = A × A
A³ = A × A × A
```

Jika memiliki invers:

```text
A⁻¹ = invers A
A⁻² = (A⁻¹)(A⁻¹)
```

---

## 5.2 Sifat Pangkat Matriks

```text
1. Aʳ Aˢ = Aʳ⁺ˢ
2. (Aʳ)ˢ = Aʳˢ
3. (Aⁿ)⁻¹ = (A⁻¹)ⁿ
```

---

# 6. Invers Matriks Diagonal

Jika:

```text
D = | d₁  0   0  |
    | 0   d₂  0  |
    | 0   0   d₃ |
```

Maka inversnya:

```text
D⁻¹ = | 1/d₁   0      0   |
       |  0    1/d₂    0   |
       |  0      0    1/d₃ |
```

Syarat:

```text
d₁, d₂, d₃ ≠ 0
```

---

# 7. Pangkat Matriks Diagonal

Jika:

```text
D = | d₁  0   0  |
    | 0   d₂  0  |
    | 0   0   d₃ |
```

Maka:

```text
Dᵏ = | d₁ᵏ   0     0  |
      | 0    d₂ᵏ    0  |
      | 0     0    d₃ᵏ |
```

Artinya:

* Pangkat hanya diterapkan pada elemen diagonal saja.

---

# Ringkasan Konsep Penting

| Konsep      | Inti Pemahaman             |
| ----------- | -------------------------- |
| Matriks Nol | Semua elemen 0             |
| Identitas   | Diagonal 1                 |
| Diagonal    | Non-diagonal 0             |
| Segitiga    | Salah satu sisi diagonal 0 |
| Simetris    | A = Aᵀ                     |
| Transpose   | Tukar baris ↔ kolom        |
| Invers      | A⁻¹ sehingga AA⁻¹ = I      |
| Pangkat     | Perkalian berulang         |

