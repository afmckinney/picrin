/**
 * See Copyright Notice in picrin.h
 */

#include "picrin.h"
#include "picrin/error.h"

int
main(int argc, char *argv[], char **envp)
{
  xFILE *stdio[3] = { xstdin, xstdout, xstderr };
  pic_state *pic;
  int status = 0;

  pic = pic_open(argc, argv, envp, stdio);

  pic_init_picrin(pic);

  pic_try {
    pic_import(pic, pic_read_cstr(pic, "(picrin main)"));
    pic_funcall(pic, "main", pic_nil_value());
  }
  pic_catch {
    pic_print_backtrace(pic, pic->err);
    status = 1;
  }

  pic_close(pic);

  return status;
}