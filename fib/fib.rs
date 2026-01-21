use num::BigInt;
use num::One;
use num::Zero;
use std::time::Instant;
//use std::mem;

fn fib(n: usize) -> BigInt {
    let mut a = BigInt::zero();
    let mut b = BigInt::one();
    for _ in 0..n {
        let tmp = b.clone();
        b += a;
        a = tmp;
        //b += &a;
        //mem::swap(&mut a, &mut b);
    }
    a
}

fn main() {
    let start = Instant::now();
    for n in 0..10_000 {
        let _ = fib(n);
    }
    //println!("fib({}) = {}", n, fib(n));
    println!("{:?}s", start.elapsed().as_secs_f64());
}
