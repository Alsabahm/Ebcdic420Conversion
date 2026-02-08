# EBCDIC-420 Arabic Conversion & Shaping Library

A portable C library for **converting AND shaping Arabic text** between:

-   **EBCDIC Code Page 420 (Arabic bilingual)**
-   **Unicode (UTF-8 / UTF-16)**
-   **Windows-1256**

Designed for **IBM z/OS, Linux on IBM Z, and cross-platform systems**
that must reliably handle Arabic text coming from mainframe
environments.

Unlike basic converters, this library ensures that **Arabic letters are
properly shaped and visually correct** after conversion\*\*, regardless
of the target encoding.

------------------------------------------------------------------------

## 🎯 Purpose

Arabic text on mainframes often becomes unreadable after conversion due
to:

-   Raw codepage mapping without shaping\
-   Disconnected Arabic letters\
-   Broken RTL presentation\
-   Mixed environments (z/OS ↔ Windows ↔ Linux)

This project provides a deterministic Arabic text pipeline where text
remains readable after conversion between:

    EBCDIC-420 ⇄ Unicode ⇄ Windows-1256

with **Arabic shaping preserved**.

------------------------------------------------------------------------

## ✨ Key Features

### 🔤 Codepage Conversion

-   EBCDIC-420 → Unicode\
-   Unicode → EBCDIC-420\
-   EBCDIC-420 → Windows-1256\
-   Windows-1256 → EBCDIC-420

### 🪶 Arabic Shaping Support

Ensures Arabic is display-ready after conversion:

-   Contextual shaping (initial / medial / final forms)
-   Prevents disconnected characters
-   Works across:
    -   z/OS
    -   Linux terminals
    -   Windows applications
-   Handles bidirectional Arabic text correctly

### 🔁 Round-Trip Safe

Text can safely travel between systems:

    Mainframe → Linux → Windows → Mainframe

without losing Arabic readability.

### ⚙️ Lightweight

-   Pure C implementation
-   Minimal dependencies (ICU)
-   Easy to embed in existing codebases
-   Suitable for batch processing

------------------------------------------------------------------------

## 🧠 Why shaping matters

Most converters only remap bytes. Arabic requires contextual shaping to
be readable.

**Without shaping**

    ا ل ع ر ب ي ة

**Correct output**

    العربية

This library ensures shaping occurs during conversion so the output is
ready for display.

------------------------------------------------------------------------

## 🏗 Supported Platforms

-   IBM z/OS USS\
-   Linux on IBM Z (s390x)\
-   Linux x86\
-   Windows (with ICU)\
-   Any POSIX system with ICU

------------------------------------------------------------------------

## 📦 Dependencies

-   C compiler (`gcc`, `clang`, or `xlc`)
-   ICU (International Components for Unicode)

Install ICU:

**Ubuntu**

``` bash
sudo apt install libicu-dev
```

**RHEL / Rocky**

``` bash
sudo dnf install libicu-devel
```

------------------------------------------------------------------------

## 🔧 Build

Clone repo:

``` bash
git clone https://github.com/Alsabahm/Ebcdic420Conversion.git
cd Ebcdic420Conversion
```

Build:

``` bash
make
```

Manual compile:

``` bash
gcc test.c converter.c -o test -licuuc -licui18n
```

z/OS example:

``` bash
xlc test.c converter.c -o test -licuuc -licui18n
```

------------------------------------------------------------------------

## 🚀 Example Usage

### Convert EBCDIC-420 → UTF-8 with shaping

``` c
convert_ebcdic420_to_utf8(input, output);
```

### Convert UTF-8 → EBCDIC-420

``` c
convert_utf8_to_ebcdic420(input, output);
```

### Convert EBCDIC-420 → Windows-1256

``` c
convert_ebcdic420_to_windows1256(input, output);
```

All outputs are **Arabic-shaped and display-ready**.

------------------------------------------------------------------------

## 🔄 Typical Workflows

-   Mainframe file migration\
-   Banking systems\
-   Government archives\
-   Middleware pipelines\
-   z/OS ↔ Windows Arabic data exchange

------------------------------------------------------------------------

## 📐 Architecture

    Input encoding
       ↓
    Decode
       ↓
    Arabic shaping
       ↓
    Re-encode to target
       ↓
    Display-ready text

------------------------------------------------------------------------

## ⚠️ Notes for z/OS

-   Ensure correct CCSID handling\
-   Use binary mode when reading datasets\
-   Confirm file tagging where required\
-   ICU must be accessible from USS

------------------------------------------------------------------------

## 📄 License

MIT License

------------------------------------------------------------------------

## 👤 Author

Built for real-world Arabic mainframe interoperability\
and systems that must reliably move Arabic text between:

-   IBM z/OS\
-   Linux\
-   Windows

------------------------------------------------------------------------

## ⭐ If this helps you

If you work with Arabic on mainframes or legacy systems,\
consider starring the repo to help others find it.
