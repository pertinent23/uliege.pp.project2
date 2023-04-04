#include <stdio.h>
#include "pnm/pnm.h"
#include "pnm/utils.h"
#include "seatest/seatest.h"

static void test_write_pnm()
{
    PNM *image1, *image2;

    load_pnm(&image1, "./test_data/Lena.pgm");
    write_pnm(image1, "./test.pgm");
    load_pnm(&image2, "./test.pgm");

    assert_int_equal(image_nb_colones(image1), image_nb_colones(image2));
    assert_int_equal(image_nb_lignes(image1), image_nb_lignes(image2));

    
    detruit_pnm(image1);
    detruit_pnm(image2);
    remove("./test.pgm");
}

static void test_equal_pnm()
{
    PNM *image1, *image2;

    load_pnm(&image1, "./test_data/Lena.pgm");
    load_pnm(&image2, "./test_data/Lena.pgm");

    assert_int_equal(image_nb_colones(image1), image_nb_colones(image2));
    assert_int_equal(image_nb_lignes(image1), image_nb_lignes(image2));

    if (image1 != NULL)
        detruit_pnm(image1);

    if (image2 != NULL)
        detruit_pnm(image2);
}

static void test_create_pnm()
{
    PNM *image;
    
    assert_int_equal(0, load_pnm(&image, "./test_data/Lena.pgm"));
    assert_true(image != NULL);

    if (image != NULL)
        detruit_pnm(image);
}

static void test_fixture_create_pnm()
{
    test_fixture_start();

    run_test(test_create_pnm);
    run_test(test_equal_pnm);
    run_test(test_write_pnm);

    test_fixture_end();
}

static void all_tests()
{
    test_fixture_create_pnm();
}

int main()
{
    return run_tests(all_tests);
}