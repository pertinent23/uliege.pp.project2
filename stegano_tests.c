#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pnm/pnm.h"
#include "stegano.h"
#include "seatest/seatest.h"

static void test_encode_from_file()
{
    PNM *image;
    char message[] = "Test Encodage", test_file[] = "test.txt";
    char *result;

    load_pnm(&image, "./test_data/Lena.pgm");
    write_message(message, test_file);

    read_message(&result, test_file);
    encode_stegano(image, 2, result);

    free(result);
    result = NULL;

    decode_stegano(image, 2, &result);

    assert_int_equal(0, strcmp(result, message));

    free(result);
    detruit_pnm(image);
    remove(test_file);
}

static void test_encode_then_decode()
{
    PNM *image;
    char message[] = "Test Encodage", *result;
    
    assert_int_equal(0, load_pnm(&image, "./test_data/Lena.pgm"));
    assert_int_equal(0, encode_stegano(image, 2, message));

    decode_stegano(image, 2, &result);

    assert_int_equal(0, strcmp(result, message));

    free(result);
    detruit_pnm(image);
}

static void test_encode()
{
    PNM *image;
    
    assert_int_equal(0, load_pnm(&image, "./test_data/Lena.pgm"));
    assert_int_equal(0, encode_stegano(image, 2, "Test Encodage"));

    detruit_pnm(image);
}

static void test_fixture_encode()
{
    test_fixture_start();

    run_test(test_encode);
    run_test(test_encode_from_file);
    run_test(test_encode_then_decode);

    test_fixture_end();
}

static void all_tests()
{
    test_fixture_encode();
}

int main()
{
    return run_tests(all_tests);
}