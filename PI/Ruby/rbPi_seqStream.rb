#!/usr/bin/ruby
require 'benchmark'

# n, c = ARGF.gets.split(' ').map!(&:to_i)
n = ARGV[0].to_i
c = ARGV[1].to_i
p(Benchmark.realtime do
  # n = 1000000

  step = 1.0 / n

  tot = (1..n).map do |i|
    x = (i - 0.5) * step
    4.0 / (1.0 + x * x)
  end.sum

  p tot / n
end)
