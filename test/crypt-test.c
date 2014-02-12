#include <check.h>
#include "../src/crypt.h"

const char *s1 = "The quick brown fox jumps over the lazy dog.";
const char *s2 = "abcdefghijklmnopqrstuvwxyzABCDEGHIJKLMNOPQRSTUVWXYZ1234567890-=<>?:[])(*&^%$#@!";

START_TEST(rot13_encode_test_s1)
{
  char *rot13e_s1 = rot13(s1);
  ck_assert_str_eq(rot13e_s1, "Gur dhvpx oebja sbk whzcf bire gur ynml qbt.");
  free(rot13e_s1);
}
END_TEST

START_TEST(rot13_encode_test_s2)
{
  char *rot13e_s2 = rot13(s2);
  ck_assert_str_eq(rot13e_s2, "nopqrstuvwxyzabcdefghijklmNOPQRTUVWXYZABCDEFGHIJKLM1234567890-=<>?:[])(*&^%$#@!");
  free(rot13e_s2);
}
END_TEST

START_TEST(rot13_decode_test_s1)
{
  char *rot13d_s1 = rot13("Gur dhvpx oebja sbk whzcf bire gur ynml qbt.");
  ck_assert_str_eq(rot13d_s1, s1);
  free(rot13d_s1);
}
END_TEST

START_TEST(rot13_decode_test_s2)
{
  char *rot13d_s2 = rot13("nopqrstuvwxyzabcdefghijklmNOPQRTUVWXYZABCDEFGHIJKLM1234567890-=<>?:[])(*&^%$#@!");
  ck_assert_str_eq(rot13d_s2, s2);
  free(rot13d_s2);
}
END_TEST

START_TEST(rot47_test_s1)
{
  char *rot47_s1 = rot47(s1);
  ck_assert_str_eq(rot47_s1, "%96 BF:4< 3C@H? 7@I ;F>AD @G6C E96 =2KJ 5@8]");
  free(rot47_s1);
}
END_TEST

START_TEST(rot47_test_s2)
{
  char *rot47_s2 = rot47(s2);
  ck_assert_str_eq(rot47_s2, "23456789:;<=>?@ABCDEFGHIJKpqrstvwxyz{|}~!\"#$%&'()*+`abcdefgh_\\lkmni,.XWYU/TSRoP");
  free(rot47_s2);
}
END_TEST

START_TEST(base64_encode_test_s1)
{
  char *b64e_s1 = base64_encode(s1);
  ck_assert_str_eq(b64e_s1, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZy4=");
  free(b64e_s1);
}
END_TEST

START_TEST(base64_encode_test_s2)
{
  char *b64e_s2 = base64_encode(s2);
  ck_assert_str_eq(b64e_s2, "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXpBQkNERUdISUpLTE1OT1BRUlNUVVZXWFlaMTIzNDU2Nzg5MC09PD4/OltdKSgqJl4lJCNAIQ==");
  free(b64e_s2);
}
END_TEST

START_TEST(base64_decode_test_s1)
{
  char *b64d_s1 = base64_decode("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZy4=");
  ck_assert_str_eq(s1, b64d_s1);
  free(b64d_s1);
}
END_TEST

START_TEST(base64_decode_test_s2)
{
  char *b64d_s2 = base64_decode("YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXpBQkNERUdISUpLTE1OT1BRUlNUVVZXWFlaMTIzNDU2Nzg5MC09PD4/OltdKSgqJl4lJCNAIQ==");
  ck_assert_str_eq(s2, b64d_s2);
  free(b64d_s2);
}
END_TEST

START_TEST(md5_hash_test_s1)
{
  char *md5h_s1 = md5(s1);
  ck_assert_str_eq(md5h_s1, "e4d909c290d0fb1ca068ffaddf22cbd0");
  free(md5h_s1);
}
END_TEST

START_TEST(md5_hash_test_s2)
{
  char *md5h_s2 = md5(s2);
  ck_assert_str_eq(md5h_s2, "d820a8d2ea3e756d4dce9c37a56830c1");
  free(md5h_s2);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, rot13_encode_test_s1);
    tcase_add_test(tc1_1, rot13_encode_test_s2);
    tcase_add_test(tc1_1, rot13_decode_test_s1);
    tcase_add_test(tc1_1, rot13_decode_test_s2);
    tcase_add_test(tc1_1, rot47_test_s1);
    tcase_add_test(tc1_1, rot47_test_s2);
    tcase_add_test(tc1_1, base64_encode_test_s1);
    tcase_add_test(tc1_1, base64_encode_test_s2);
    tcase_add_test(tc1_1, base64_decode_test_s1);
    tcase_add_test(tc1_1, base64_decode_test_s2);
    tcase_add_test(tc1_1, md5_hash_test_s1);
    tcase_add_test(tc1_1, md5_hash_test_s2);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
