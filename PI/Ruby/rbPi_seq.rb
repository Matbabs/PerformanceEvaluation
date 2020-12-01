#!/usr/bin/ruby
require 'benchmark'

n, c = ARGF.gets.split(' ').map!(&:to_i)
p(Benchmark.realtime do
  # n = 1_000_000
  step = 1 / n.to_f
  sum = 0.0

  (1..n).each do |i|
    x = (i - 0.5) * step
    sum += 4.0 / (1.0 + x * x)
  end

  p sum * step
end)
