fn F32 math_sqrt(F32 number)
{
	I32 i;
	F32 x, y;
	x = number * 0.5;
	y = number;
	i = * (I32 *) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(I32 *) &i;
	y = y * (1.5 - (x * y * y));
	y = y * (1.5 - (x * y * y));
	return number * y;
}
