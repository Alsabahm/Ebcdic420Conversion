# Ebcdic420Conversion

**Ebcdic420Conversion** is a lightweight **C library** for converting  
**EBCDIC Code Page 420 (Arabic bilingual, IBM-420)** ↔ **Unicode (UTF-8/UTF-16)** and **Windows-1256**.

Built on top of [ICU (International Components for Unicode)](https://icu.unicode.org/).  
Tested on **z/OS mainframes**, works on **Linux** and **Windows**.  
MIT Licensed.

---

## ✨ Features

- 🔄 EBCDIC-420 → Unicode (UTF-8 / UTF-16)
- 🔄 Unicode → EBCDIC-420
- 🔄 EBCDIC-420 → Windows-1256
- ✅ Round-trip conversion tests
- ⚡ Based on ICU (tested with ICU58+)

---

## 🚀 Getting Started

### Prerequisites
- C compiler (GCC, Clang, or MSVC)
- [ICU development libraries](https://icu.unicode.org/download) installed

### Build
```bash
git clone https://github.com/Alsabahm/Ebcdic420Conversion.git
cd Ebcdic420Conversion
gcc -o ebcdic420 Library/*.c -licuuc -licui18n
