#include <bmp_header.h>
#include <carrier.h>
#include <encrypt.h>
#include <hidden_file.h>
#include <jobs.h>
#include <lsb.h>
#include <payload.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h>

void lsb_1();

int main()
{
    create_suite("General Test");
    add_test(lsb_1);
    run_suite();
    clear_suite();
}

void lsb_1()
{
    uint32_t s;
    bmp_file bmp_f = read_bmp("ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;

    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);

    payload p = extract_payload(l, c);

    FILE *f = fopen("miicapa", "w");
    s=extract_payload_size(l,c);
    fwrite(p->content, sizeof(uint8_t), s, f);

    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);

    assert_true(1 == 1);
}
