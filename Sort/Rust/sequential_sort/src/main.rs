use std::env;
use std::time::{Instant};
use rand::Rng;

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() == 2 {

        let mut vec = Vec::new();
        let nb_elems = args[1].parse::<i32>().unwrap();
        let mut rng = rand::thread_rng();

        for _i in 0..nb_elems{
            vec.push(rng.gen_range(0, nb_elems));
        }

        let start_time = Instant::now();
        vec.sort();
        //println!("{:?}", vec);
        let end_time = Instant::now();
    
        println!("{:?}", end_time.duration_since(start_time));

    } else {
        println!("Usage: <number of elements>");
    }
}