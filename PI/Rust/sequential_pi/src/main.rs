use std::env;
use std::time::{Instant};

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() == 3 {

        let nb_steps = args[1].parse::<i32>().unwrap();
        let mut sum: f64 = 0.0;
        let steps: f64 = 1.0 / nb_steps as f64;
        let mut x: f64;
        let p: f64;

        let start_time = Instant::now();
    
        for i in 0..nb_steps {
            x = (i as f64 -0.5)*steps;
            sum += 4.0 / (1.0 + x * x);
        }
    
        p = steps * sum;

        let end_time = Instant::now();
    
        println!("{:.64}", p);
        println!("{:?}", end_time.duration_since(start_time));

    } else {
        println!("Usage: <number of iterations> <number of threads>");
    }
}