#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp/board.h"
#include "tusb.h"
#include "nec_receive.h"

int main(void)
{
  stdio_init_all();
  board_init();
  tusb_init();
  PIO pio = pio0;
  uint rx_gpio = 27;
  int rx_sm = nec_rx_init (pio, rx_gpio);
  uint8_t rx_address, rx_data;
  while (1)
  {
    tud_task();
    if ( tud_hid_n_ready(0) )
    {
      uint8_t kcode[6] = { 0 };
      while (!pio_sm_is_rx_fifo_empty (pio, rx_sm)) {
        uint32_t rx_frame = pio_sm_get (pio, rx_sm);
        if (nec_decode_frame (rx_frame, &rx_address, &rx_data)) {
          printf ("received: %02x, %02x\n", rx_address, rx_data);
          if(rx_data == 0x06) {
            kcode[0] = 0x52; //UP
          }
          if (rx_data == 0x44) {
            kcode[0] = 0x51; //DOWN
          }
          if(rx_data == 0x40) {
            kcode[0] = 0x4f; //Right
          }
          if (rx_data == 0x47) {
            kcode[0] = 0x50; //Left
          }
          if(rx_data == 0x07) {
            kcode[0] = HID_KEY_ENTER;
          }
          if (rx_data == 0x5e) {
            kcode[0] = HID_KEY_BACKSPACE;
          }
          if(rx_data == 0x16) {
            kcode[0] = HID_KEY_PAGE_UP;
          }
          if (rx_data == 0x5b) {
            kcode[0] = HID_KEY_PAGE_DOWN;
          }
          tud_hid_n_keyboard_report(0, 0, 0, kcode);
        } else {
          printf ("received: %08x\n", rx_frame);
        }
      }
      tud_hid_n_keyboard_report(0, 0, 0, NULL);
    }
  }
  return 0;
}


uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;
  return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) bufsize;
}