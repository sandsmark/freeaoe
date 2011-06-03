/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma pack(push, 1)

typedef struct {
    short       name1_length;
    short       id;
    short       language;
    raw         unknown01[4];
    short       graphic_default;
    short       minus1_01;
    short       graphic_die;
    short       minus1_02;
    char        zero_01;
    short       hitpoints;
    float       lineofsight;
    char        garrison;
    float       unknown02_03[3];
    short       sounds01[2];
    short       deadunit;
    short       unknown02_05;
    short       icon;
    char        notineditor;
    short       unknown02_07[6];
    float       unknown02_08[2];
    char        unknown02_09_01;
    char        unknown02_09_02;
    short       unknown02_09_03;
    char        unknown02_09_04;
    short       unknown02_09_05;
    float       unknown02_10;
    raw         unknown02_11[5];
    float       unknown02_12;
    raw         unknown02_13[26];
    float       unknown02_14[3];
    short       unknown02_15;
    float       unknown02_16;
    raw         unknown02_17[3];
    float       unknown02_18;
    raw         unknown02_19[8];
} genie_unit_head;

typedef struct {
    float       speed;
} genie_unit_part2;

typedef struct {
    short       graphic_walk;
} genie_unit_part3;

typedef struct {
    char        unknown18[37];
} genie_unit_part4;

typedef struct {
    short       unknown19_01;
    float       unknown19_02;
    char        unknown19_03;
    short       unknown19_04;
    char        unknown19_05;
    float       unknown19_06[2];
    char        unknown19_07[9];
    float       unknown19_08;
    char        unknown19_09[4];
    short       unknown20;
    float       unknown21[2];
    char        unknown22[5];
    short       sound_move;
    short       sound_stop;
    char        unknown24;
    short       unknown25;
} genie_unit_part5;

typedef struct {
    raw         unknown18b[2];
} genie_unit_part6;

typedef struct {
    short       unknown28;
} genie_unit_part7;

typedef struct {
    short       unknown29_01;
    float       unknown29_02[3];
    short       unknown29_03;
    char        unknown29_04;
} genie_unit_part8;

typedef struct {
    short       unknown27;
    float       unknown31_01[3];
    short       unknown31_02;
    char        unknown31_03;
    float       unknown31_04[4];
    char        unknown31_05;
    float       unknown31_06[2];
    short       unknown31_07[3];
    float       unknown31_08[2];
    char        unknown31_09[5];
    float       unknown31_10;
} genie_unit_part9;

typedef struct {
    float       attack_range;
    float       attack_radius;
    float       attack_reload01;
    short       projectile;
    short       unknown32_02;
    char        unknown32_03[3];
    float       unknown32_04[3];
    char        unknown32_05;
    float       unknown32_06[2];
} genie_unit_part10;

typedef struct {
    short       unknown33_01[4];
    float       unknown33_02[2];
    char        unknown33_03;
    float       unknown33_04[2];
    short       unknown33_06[3];
    float       unknown33_07[2];
    short       cost_01_type;
    short       cost_01_amount;
    short       cost_01_used;
    short       cost_02_type;
    short       cost_02_amount;
    short       cost_02_used;
    short       cost_03_type;
    short       cost_03_amount;
    short       cost_03_used;
    short       cost_time;
    short       unknown33_08;
    char        unknown33_09;
    long        unknown33_10[2];
    short       unknown33_11;
    long        unknown33_12;
    float       unknown33_13;
    char        unknown33_14;
    float       unknown33_15[3];
    long        unknown33_16[2];
    char        unknown33_17;
    short       unknown33_18[2];
} genie_unit_part11;

typedef struct {
    short       graphic_attack;
    short       armour_displayed;
    short       attack_displayed;
} genie_unit_part12;

typedef struct {
    float       attack_range_displayed;
    float       attack_reload02;
    short       cost_01_type;
    short       cost_01_amount;
    short       cost_01_used;
    short       cost_02_type;
    short       cost_02_amount;
    short       cost_02_used;
    short       unknown35_04[3];
    short       cost_time;
    short       unknown35_05[5];
    char        unknown35_06;
    short       unknown35_07[3];
    float       unknown35_08;
    char        unknown35_09;
    float       unknown35_10[3];
    long        unknown35_11[2];
    char        unknown35_12;
    short       duraarmour_displayed;
} genie_unit_part14;

typedef struct {
    short       unknown36_01[4];
    char        unknown36_02;
    short       unknown36_03;
    float       unknown36_04[2];
    short       unknown36_05;
    float       unknown36_06[2];
    short       unknown36_07;
    long        unknown36_08[2];
    short       unknown36_09;
    long        unknown36_10[2];
    short       unknown36_11[4];
    char        unknown36_12;
    float       unknown36_13;
    long        unknown36_14;
    short       unknown36_15;
    char        unknown36_16[6];
} genie_unit_part15;

#pragma pack(pop)
