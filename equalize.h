// Copyright 2023-2024 Balan Matei-Cristian (matei.balan@stud.acs.upb.ro)

#ifndef EQUALIZE_H_
#define EQUALIZE_H_

int clamp(double num);

void equalize_img(struct image *img, int allocated);

#endif
