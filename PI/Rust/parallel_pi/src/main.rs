use std::thread;
use std::sync::{Arc, Mutex};

#[derive(Copy, Clone)]
struct Step{
    start: i64,
    inc: i64,
    res: f64
}

fn main() {
    let nb_steps = 1000000;
    let nb_threads = 40;
    let mut steps = Vec::with_capacity(nb_threads);
    let bloc = nb_steps/nb_threads;
    let safe_pi = Arc::new(Mutex::new(0.0));

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
        thread::spawn(move || {
            for k in stps[i].start..stps[i].start+stps[i].inc{
                stps[i].res += (4 * i64::pow(-1,k as u32)) as f64 / ((2*k + 1)) as f64;
            }
            let mut pi = pi.lock().unwrap();
            *pi += stps[i].res;
        })
    })
    .collect::<Vec<thread::JoinHandle<_>>>();  
    for thread in handles {
        thread.join().unwrap();
    }
    println!("{:?}",safe_pi);
}
