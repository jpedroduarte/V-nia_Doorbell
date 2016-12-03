#define size_offset 5

/*
 * 11100000
 * bit0 to bit4 the morse sequence (0's)
 * bit5 to bit8 size of the sequence (1's)
 */

const unsigned char morse[36]={
    2<<size_offset | 0b01,      //A
    4<<size_offset | 0b1000,    //B
    4<<size_offset | 0b1010,    //C
    3<<size_offset | 0b100,     //D
    1<<size_offset | 0b0,       //E
    4<<size_offset | 0b0010,    //F
    3<<size_offset | 0b110,     //G
    4<<size_offset | 0b0000,    //H
    2<<size_offset | 0b00,      //I
    4<<size_offset | 0b0111,    //J
    3<<size_offset | 0b101,     //K
    4<<size_offset | 0b0100,    //L
    2<<size_offset | 0b11,      //M
    2<<size_offset | 0b10,      //N
    3<<size_offset | 0b111,     //O
    4<<size_offset | 0b0110,    //P
    4<<size_offset | 0b1101,    //Q
	3<<size_offset | 0b010,     //R
	3<<size_offset | 0b000,     //S
	1<<size_offset | 0b1,       //T
	3<<size_offset | 0b001,     //U
	4<<size_offset | 0b0001,    //V
	3<<size_offset | 0b011,     //W
	4<<size_offset | 0b1001,    //X
	4<<size_offset | 0b1011,    //Y
	4<<size_offset | 0b1100,    //Z
    5<<size_offset | 0b11111,   //0
    5<<size_offset | 0b01111,   //1
    5<<size_offset | 0b00111,   //2
    5<<size_offset | 0b00011,   //3
    5<<size_offset | 0b00001,   //4
    5<<size_offset | 0b00000,   //5
    5<<size_offset | 0b10000,   //6
    5<<size_offset | 0b11000,   //7
    5<<size_offset | 0b11100,   //8
    5<<size_offset | 0b11110    //9
};
