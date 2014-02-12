#include "../src/crypt.h"
#include <check.h>

const char *s = "The quick fox jumps over the lazy brown dog.";

START_TEST(rot13_test)
{
  char *rot13_s = rot13(s);
  ck_assert_str_eq(rot13_s, "Gur dhvpx sbk whzcf bire gur ynml oebja qbt.");
  free(rot13_s);

}
END_TEST

START_TEST(rot47_test)
{
  char *rot47_s = rot47(s);
  ck_assert_str_eq(rot47_s, "%96 BF:4< 7@I ;F>AD @G6C E96 =2KJ 3C@H? 5@8]");
  free(rot47_s);

}
END_TEST

START_TEST(base64_encode_test)
{
  char *b64e_s = base64_encode(s);
  ck_assert_str_eq(b64e_s, "VGhlIHF1aWNrIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGJyb3duIGRvZy4=");
  free(b64e_s);

}
END_TEST

START_TEST(base64_decode_test)
{
  char *b64d_s = base64_decode("VGhlIHF1aWNrIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGJyb3duIGRvZy4=");
  ck_assert_str_eq(s, b64d_s);
  free(b64d_s);

}
END_TEST

START_TEST(md5_hash_test)
{
  char *md5h_s = md5(s);
  ck_assert_str_eq(md5h_s, "9486f5fbd1c2e79140f4a4eb4e1020d7");
  free(md5h_s);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, rot13_test);
    tcase_add_test(tc1_1, rot47_test);
    tcase_add_test(tc1_1, base64_encode_test);
    tcase_add_test(tc1_1, base64_decode_test);
    tcase_add_test(tc1_1, md5_hash_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}