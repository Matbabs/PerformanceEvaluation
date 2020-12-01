
fn main() {

    let nb_steps = 1000000;
    let mut sum: f64 = 0.0;
    let steps: f64 = 1.0 / nb_steps as f64;
    let mut x: f64;
    let p: f64;

    for i in 0..nb_steps {
        x = (i as f64 -0.5)*steps;
        sum += 4.0 / (1.0 + x * x);
    }

    p = steps * sum;

    println!("{:.64}", p);
}