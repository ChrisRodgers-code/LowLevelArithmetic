static MAX:i32 = 31;
static MANT_MAX:i32 = 22;

pub fn f_point(a: u64) -> (){
	let raw_mant = a & 0x003fffff;
	println!("The raw mantisa is: {:x}", raw_mant);

	let mut mant:f32 = 0.0;
	for i in 0..MAX-8{
		if (a & (1 << (MANT_MAX -i))) != 0{
			mant += 1.0/((i+1) as f32).exp2();
		} else {
			continue;
		}
	}
	mant += 1.0_f32;
	println!("the mantisa is: {}", mant);

	let mut a_e:u64 = a & 0x7f800000;
	a_e = a_e >> 23;

	println!("The raw exponent part is: {:x}", a_e);

	let val:f64;
	val = ((a_e as f64) - 127_f64)*2.0_f64.log10();

	let round_val:f64;
	if val < 0.0 {
		round_val = val.ceil();
	} else {
		round_val = val.floor();
	}

	let frac_val:f64 = val - round_val;

	if (a & 0x80000000) != 0 {
		println!("The floating point value is: -{}e{}", mant*10_f32.powf(frac_val as f32), (round_val as i32));
	} else {
		println!("The floating point value is: {}e{}", mant*10_f32.powf(frac_val as f32), (round_val as i32));
	}
}