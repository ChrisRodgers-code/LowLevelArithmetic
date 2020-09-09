static MAX:i32 = 31;
static MANT_MAX:i32 = 22;

fn float_sign(a: u64) -> f64 {
	let sign: f64;
	if (a & 0x80000000) != 0 {
		sign = -1.0 as f64;
	} else {
		sign = 1.0 as f64;
	}
	return sign;
}

fn exponent(a: u64) -> f64 {
	let mut a_e = a & 0x7f800000;
	a_e = a_e >> 23;
	let val = ((a_e as f64) - 127_f64)*2.0_f64.log10();
	return val;
}

fn mantissa(a: u64) -> f64 {
	let mut mant:f64 = 0.0;
	for i in 0..MAX-8{
		if (a & (1 << (MANT_MAX -i))) != 0{
			mant += 1.0/((i+1) as f64).exp2();
		} else {
			continue;
		}
	}
	mant += 1.0_f64;
	return mant;
}

pub fn f_point(a: u64) -> (){
	println!("The input register is: {:x}", a);

	let mant = mantissa(a);
	println!("the mantisa is: {}", mant);

	let expon = exponent(a);
	println!("The exponent is: {}", expon);

	let sign = float_sign(a);
	println!("The sign is: {}", sign);

	let float_val = sign*mant*10_f64.powf(expon);
	println!("The floating point value of the register is: {:?}", float_val);
}
