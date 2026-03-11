# Rangkuman Materi

# Data Modeling Using Entity Relationship (ER) Model

Materi ini membahas **cara merancang database menggunakan model ER (Entity Relationship)**.

ER Model digunakan pada tahap **perancangan konseptual database** sebelum database dibuat menjadi tabel.

---

# 1. Proses Perancangan Database

Perancangan database biasanya dilakukan melalui beberapa tahap:

1️⃣ **Requirement Analysis**
Mengumpulkan kebutuhan sistem dari pengguna.

2️⃣ **Conceptual Design**
Membuat model konseptual menggunakan **ER Diagram**.

3️⃣ **Logical Design**
Mengubah ER Diagram menjadi **tabel relasional**.

4️⃣ **Physical Design**
Menentukan cara penyimpanan data di sistem database.

---

# 2. Contoh Kasus Database Perusahaan (COMPANY)

Untuk memahami ER Model digunakan contoh sistem database **perusahaan**.

Database harus menyimpan informasi tentang:

### Departemen

Setiap **DEPARTMENT** memiliki:

* department name
* department number
* manager
* manager start date
* department locations

---

### Project

Setiap **PROJECT** memiliki:

* project name
* project number
* project location

Setiap project dikontrol oleh **departemen tertentu**.

---

### Employee

Setiap **EMPLOYEE** memiliki data:

* social security number
* address
* salary
* sex
* birthdate

Setiap employee:

* bekerja pada **1 departemen**
* dapat bekerja pada **beberapa project**

---

### Jam kerja

Database juga menyimpan:

Jumlah jam kerja per minggu employee pada project.

---

### Supervisor

Setiap employee memiliki **supervisor langsung**.

---

### Dependent

Employee dapat memiliki **DEPENDENT** (tanggungan).

Data dependent:

* name
* sex
* birthdate
* relationship

---

# 3. Konsep Utama ER Model

ER Model memiliki **3 konsep utama**:

### 1️⃣ Entity

### 2️⃣ Attribute

### 3️⃣ Relationship

Ketiga konsep ini digunakan untuk membuat **ER Diagram**.

---

# 4. Entity

**Entity** adalah objek di dunia nyata yang dapat disimpan datanya.

Contoh entity:

* EMPLOYEE
* DEPARTMENT
* PROJECT
* DEPENDENT

---

## Entity Type

Entity type adalah **kategori entity**.

Contoh:

```
EMPLOYEE
```

Entity instance:

```
Employee1
Employee2
Employee3
```

Semua instance ini disebut **Entity Set**.

---

# 5. Attribute

**Attribute** adalah karakteristik dari entity.

Contoh:

EMPLOYEE memiliki attribute:

* Name
* Address
* Salary
* Birthdate

---

# 6. Jenis Attribute

ER Model mengenal beberapa jenis attribute.

---

## 1. Simple Attribute

Attribute yang **tidak dapat dipecah lagi**.

Contoh:

```
Salary
Age
Gender
```

---

## 2. Composite Attribute

Attribute yang dapat dipecah menjadi bagian kecil.

Contoh:

```
Address
```

dapat dipecah menjadi:

* Street
* City
* Zip code

---

## 3. Multivalued Attribute

Attribute yang dapat memiliki **lebih dari satu nilai**.

Contoh:

```
Phone number
```

Seseorang bisa punya:

```
0812
0821
0856
```

---

## 4. Derived Attribute

Attribute yang **dihitung dari attribute lain**.

Contoh:

```
Age
```

dihitung dari:

```
Birthdate
```

---

# 7. Key Attribute

**Key Attribute** adalah attribute yang **membedakan setiap entity secara unik**.

Contoh:

EMPLOYEE

```
SSN (Social Security Number)
```

Karena tidak ada dua employee dengan SSN sama.

---

# 8. Relationship

**Relationship** adalah hubungan antara entity.

Contoh:

```
EMPLOYEE works on PROJECT
```

---

## Relationship Type

Relationship type adalah **jenis hubungan**.

Contoh:

```
WORKS_ON
MANAGES
WORKS_FOR
```

---

## Relationship Instance

Relationship instance adalah **hubungan nyata antar entity**.

Contoh:

```
John works on ProjectX
```

---

# 9. Degree of Relationship

Degree adalah jumlah entity yang terlibat dalam relationship.

### Binary Relationship

Hubungan antara **2 entity**.

Contoh:

```
EMPLOYEE — WORKS_ON — PROJECT
```

---

### Unary / Recursive Relationship

Entity berhubungan dengan **entity yang sama**.

Contoh:

```
EMPLOYEE supervises EMPLOYEE
```

Supervisor → Employee

---

### Ternary Relationship

Hubungan antara **3 entity**.

Contoh:

```
SUPPLIER supplies PART to PROJECT
```

---

# 10. Relationship pada Contoh COMPANY

Dari requirement sistem perusahaan ditemukan beberapa relationship:

### WORKS_FOR

EMPLOYEE bekerja untuk DEPARTMENT

---

### MANAGES

EMPLOYEE mengelola DEPARTMENT

---

### CONTROLS

DEPARTMENT mengontrol PROJECT

---

### WORKS_ON

EMPLOYEE bekerja pada PROJECT

---

### SUPERVISION

EMPLOYEE mengawasi EMPLOYEE lain

---

### DEPENDENTS_OF

EMPLOYEE memiliki DEPENDENT

---

# 11. Recursive Relationship

Recursive relationship terjadi ketika entity berhubungan dengan entity yang sama.

Contoh:

```
SUPERVISION
```

EMPLOYEE berperan sebagai:

* supervisor
* subordinate

---

# 12. Weak Entity

**Weak Entity** adalah entity yang **tidak memiliki primary key sendiri**.

Weak entity bergantung pada entity lain.

---

## Contoh

DEPENDENT adalah weak entity.

Karena:

Nama dependent saja **tidak cukup untuk identifikasi**.

Misalnya:

```
Nama: Anna
```

Bisa ada banyak Anna.

Maka identifikasi:

```
Employee + DependentName
```

---

## Partial Key

Weak entity memiliki **partial key**.

Contoh:

```
DependentName
```

---

# 13. Relationship Constraints

Constraint digunakan untuk membatasi hubungan antar entity.

Ada dua jenis utama:

---

# 14. Cardinality Ratio

Menunjukkan **jumlah maksimum hubungan**.

Jenisnya:

### 1 : 1

Satu entity berhubungan dengan satu entity.

Contoh:
Satu orang → satu paspor

---

### 1 : N

Satu entity berhubungan dengan banyak entity.

Contoh:

```
DEPARTMENT → EMPLOYEE
```

Satu departemen punya banyak employee.

---

### N : 1

Kebalikan dari 1:N.

---

### M : N

Banyak ke banyak.

Contoh:

```
EMPLOYEE ↔ PROJECT
```

Employee bisa kerja di banyak project
Project bisa punya banyak employee

---

# 15. Participation Constraint

Menentukan **apakah entity wajib ikut relationship atau tidak**.

---

## Total Participation

Entity **harus ikut relationship**.

Digambar dengan **double line**.

Contoh:
Setiap department **harus punya manager**.

---

## Partial Participation

Entity **tidak wajib ikut relationship**.

Digambar dengan **single line**.

---

# 16. Min-Max Notation

Cara lain menunjukkan constraint adalah:

```
(min, max)
```

Contoh:

EMPLOYEE dalam MANAGES

```
(0,1)
```

artinya:
Employee bisa:

* tidak jadi manager
* atau manager satu department

---

Contoh lain:

DEPARTMENT dalam MANAGES

```
(1,1)
```

artinya:

Department harus punya **tepat satu manager**.

---

# 17. Attribute pada Relationship

Relationship juga bisa memiliki attribute.

Contoh:

Relationship:

```
WORKS_ON
```

Attribute:

```
HoursPerWeek
```

Menunjukkan berapa jam employee bekerja pada project.

---

# 18. Notasi ER Diagram

Beberapa simbol dalam ER Diagram:

| Simbol           | Artinya               |
| ---------------- | --------------------- |
| Rectangle        | Entity                |
| Diamond          | Relationship          |
| Oval             | Attribute             |
| Double Oval      | Multivalued attribute |
| Dashed Oval      | Derived attribute     |
| Double Rectangle | Weak entity           |

---

# 19. UML Class Diagram sebagai Alternatif

Selain ER Diagram, database juga bisa dimodelkan menggunakan:

**UML Class Diagram**

Ciri UML:

Class memiliki 3 bagian:

1️⃣ Nama class
2️⃣ Attribute
3️⃣ Operations (method)

Relationship disebut **association**.

---

# 20. Relationship Degree Lebih Tinggi

Relationship tidak selalu binary.

Ada juga:

### Ternary relationship (3 entity)

Contoh:

```
Supplier — Part — Project
```

---

### N-ary relationship

Hubungan lebih dari 3 entity.

Namun:

Relasi kompleks lebih sulit dianalisis.

---

# 21. Tools untuk Data Modeling

Beberapa software untuk membuat ER Diagram:

* ERWin
* ER Studio
* S-Designer
* Enterprise Application Suite

Kelebihan:

* mudah digunakan
* visual
* dokumentasi sistem

Kekurangan:

* beberapa tools lebih fokus ke relational schema daripada ER concept.

---

# 22. Extended ER Model (EER)

ER Model dapat diperluas menjadi **EER (Extended ER)**.

EER menambahkan konsep:

* specialization
* generalization
* subclass
* superclass

Ini akan dibahas pada bab berikutnya.

---

# Kesimpulan Materi ER Model

Hal penting dari ER Model:

1️⃣ ER Model digunakan untuk **perancangan database konseptual**

2️⃣ Tiga komponen utama:

* Entity
* Attribute
* Relationship

3️⃣ Relationship memiliki:

* cardinality
* participation constraint

4️⃣ Weak entity bergantung pada entity lain

5️⃣ ER Diagram digunakan untuk **memvisualisasikan struktur database**


* atau **mengajari cara cepat menggambar ERD yang benar (yang dosen biasanya mau)**.
