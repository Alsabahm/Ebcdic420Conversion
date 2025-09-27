# Ebcdic420Conversion

A lightweight C library for converting **EBCDIC Code Page 420 (Arabic bilingual)**  
to **Unicode (UTF-8/UTF-16)** or **Windows-1256**, and vice versa.  

Designed for **z/OS UNIX System Services (USS)** and **Linux on IBM Z (z/Linux)**,  
but also portable to x86 Linux and Windows.  

---

## ✨ Features

- ✅ Convert **EBCDIC-420 (Arabic)** → **Unicode (UTF-8/UTF-16)**  
- ✅ Convert **Unicode (UTF-8/UTF-16)** → **EBCDIC-420**  
- ✅ Convert **EBCDIC-420** → **Windows-1256**  
- ✅ Round-trip conversion tests included  
- ✅ Lightweight wrapper over ICU (International Components for Unicode)  

---

## 🖥️ Platform Support

- **z/OS UNIX System Services (USS)**  
- **Linux on IBM Z (z/Linux partitions)**  
- **Linux (x86) for testing/cross-development**  
- **Windows** (with ICU installed)

---

## 📦 Installation

### Prerequisites
- C compiler: `gcc`, `clang`, or `xlc` (on z/OS USS)  
- [ICU libraries](https://icu.unicode.org/download) installed  

### Build on Linux / z/OS Linux partition
```bash
git clone https://github.com/Alsabahm/Ebcdic420Conversion.git

