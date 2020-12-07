use std::thread;
use std::sync::{Arc, Mutex};
use std::env;
use std::time::{Instant};

#[derive(Copy, Clone)]
struct Step{
    start: i64,
    inc: i64,
    res: f64
}

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() == 3 {

        let nb_steps = args[1].parse::<i32>().unwrap();
        let nb_threads = args[2].parse::<i32>().unwrap();
        let mut steps = Vec::with_capacity(nb_threads as usize);
        let bloc = nb_steps/i32::from(nb_threads) ;
        let safe_pi = Arc::new(Mutex::new(0.0));

        let start_time = Instant::now();
    
        let handles = (0..nb_threads)
        .into_iter()
        .map(|i| {
            steps.push(Step{
                start:(bloc*i) as i64,
                inc:bloc as i64,
                res:0.0
            });
            let pi = Arc::clone(&safe_pi);
            let mut stps = steps.clone();
            let ii = i as usize;
            thread::spawn(move || {
                for k in stps[ii].start..stps[ii].start+stps[ii].inc{
                    stps[ii].res += (4 * i64::pow(-1,k as u32)) as f64 / ((2*k + 1)) as f64;
                }
                let mut pi = pi.lock().unwrap();
                *pi += stps[ii].res;
            })
        })
        .collect::<Vec<thread::JoinHandle<_>>>();  
        for thread in handles {
            thread.join().unwrap();
        }

        let end_time = Instant::now();

        println!("{:?}",safe_pi);
        println!("{:?}", end_time.duration_since(start_time));

    } else {
        println!("Usage: <number of iterations> <number of threads>");
    }
}
