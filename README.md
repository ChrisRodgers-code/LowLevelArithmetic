# LowLevelArithmetic

This respository is home to some of the C and Rust code that I have written to try and understand how computers do arithmetic at the level of bare metal. My code is not anywhere near looking at the bare metal. Instead it just looks at the logic of how one would go about doing these manipulations.

In the C implementation of floating point arithmetic, there is a misunderstanding of how the mantisa and the exponent are calculated for the IEEE 754 standard. These misunderstandings are fixed in the Rust implementation.

These misunderstandings do raise some interesting questions. So, until I find satisfactory answers I am going to leave the C implementation as is.
