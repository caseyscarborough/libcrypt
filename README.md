# libcrypt

libcrypt is a simple library used for encryption, hashing, and encoding in C. It is currently a work in progress.

## Using the Library

To use the library, include the [`crypt.h`](https://github.com/caseyscarborough/libcrypt/blob/master/src/crypt.h) and [`crypt.c`](https://github.com/caseyscarborough/libcrypt/blob/master/src/crypt.c) files in your project. Then, include the [`crypt.h`](https://github.com/caseyscarborough/libcrypt/blob/master/src/crypt.h) file at the top of each file you'd like to use it's methods in. See [`test/crypt-test.c`](https://github.com/caseyscarborough/libcrypt/blob/master/test/crypt-test.c) for example usage.

To run the test file or the Base64 converter, run `make` from the project directory.

## Methods

The following methods are available in the [libcrypt](https://github.com/caseyscarborough/libcrypt) library. _Note that these methods return pre-allocated blocks of memory, and it is up to the user of the method to free the memory after use (shown below)._

#### rot13

This method encodes a string of text using the [ROT13](http://en.wikipedia.org/wiki/ROT13) cipher.

```c
char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
char *rot13_encoded_text = rot13(text);

printf("%s\n", rot13_encoded_text);
// Outputs: Gur Dhvpx Oebja Sbk Whzcf Bire Gur Ynml Qbt.

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

#### md5

This method hashes a given string using the [MD5](http://en.wikipedia.org/wiki/MD5) hashing algorithm.

```c
char *text = "The quick brown fox jumps over the lazy dog."
char *md5_text = md5(text);
printf("%s\n", md5_text);
// Outputs: e4d909c290d0fb1ca068ffaddf22cbd0

free(md5_text);
```

#### generate_uuid

This method This method generates a version 4 [Universally Unique Identifier](http://en.wikipedia.org/wiki/Universally_unique_identifier#Version_4_.28random.29), which is randomly generated.

```c
char *uuid = generate_uuid();
printf("%s\n", uuid);
// Outputs 3586BD54-55C8-42D8-BE0E-74308A5B9D22

free(uuid);
```

## Utilities

### Base64 Converter

Included in this library is a Base64 file converter utility, located in the file [`utils/b64.c`](https://github.com/caseyscarborough/libcrypt/blob/master/utils/b64.c). This utility will convert the contents of a file to or from Base64 encoded data.

```bash
# Build the executables
$ make && cd bin

# Encode a file
$ ./b64 -e input.txt output.txt

# Decode a file
$ ./b64 -e encoded.txt decoded.txt

# Print the help menu
$ ./b64 -h
```

### MD5 Hasher

The MD5 Hasher utility is located in the file [`utils/md5.c`](https://github.com/caseyscarborough/libcrypt/blob/master/utils/md5.c). This utility will MD5 hash the contents of a file or a string.

```bash
$ make && cd bin

# Hash a string
$ ./md5 -s "The quick brown fox jumps over the lazy dog."
e4d909c290d0fb1ca068ffaddf22cbd0

# Hash a file's contents
$ ./md5 -f sample.txt
322a166e1402bd9ff18e1ce67fe69e61  sample.txt

# Print the help menu
$ ./md5 -h
```

Either of these compiled utilities can then be copied to somewhere in your __PATH__ to be available from anywhere.

## Running the Tests

Tests are written using the [Check](http://check.sourceforge.net/) unit testing framework. The tests are located at [`crypt-test.c`](https://github.com/caseyscarborough/libcrypt/blob/master/test/crypt-test.c), and can be compiled using `make test`. The check library [needs to be installed](http://check.sourceforge.net/web/install.html).

```bash
make test
# gcc -Wall test/crypt-test.c -o test/crypt-test -lcheck

test/crypt-test
# Running suite(s): Core
# 100%: Checks: 12, Failures: 0, Errors: 0
```
