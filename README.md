# libcrypt

libcrypt is a simple library used for encryption, hashing, and encoding in C. It is currently a work in progress.

## Methods

#### rot13

This method encodes a string of text using the [ROT13](http://en.wikipedia.org/wiki/ROT13) cipher.

```c
char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
char *rot13_encoded_text = rot13(text);

printf("%s\n", rot13_encoded_text);
// Outputs: ur Dhvpx Oebja Sbk Whzcf Bire Gur Ynml Qbt.

free(rot13_encoded_text);
```

#### rot47

This method encodes a string of text using the [ROT47](http://en.wikipedia.org/wiki/ROT47#Variants) cipher.

```c
char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
char *rot47_encoded_text = rot13(text);

printf("%s\n", rot47_encoded_text);
// Outputs: %96 "F:4< qC@H? u@I yF>AD ~G6C %96 {2KJ s@8]

free(rot47_encoded_text);
```

#### base64_encode

This method encodes text using the [Base64](http://en.wikipedia.org/wiki/Base64) encoding scheme.

```c
char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
char *base64_encoded_text = base64_encode(text);
printf("%s\n", base64_encoded_text);
// Outputs: VGhlIFF1aWNrIEJyb3duIEZveCBKdW1wcyBPdmVyIFRoZSBMYXp5IERvZy4=

free(base64_encoded_text);
```

#### base64_decode

This method decodes [Base64](http://en.wikipedia.org/wiki/Base64) encoded text.

```c
char *text = "VGhpcyBpcyBzb21lIGR1bW15IHRleHQgdG8gYmUgZW5jb2RlZCBhbmQgZGVjb2RlZC4=";
char *base64_decoded_text = base64_decode(text);
printf("%s\n", base64_decoded_text);
// Outputs: This is some dummy text to be encoded and decoded.

free(base64_decoded_text);
```

## Using the Library

To use the library, include the `crypt.h` and `crypt.c` files in your project. Then, include the `crypt.h` file at the top of each file you'd like to use it's methods in. See `test.c` for example usage.