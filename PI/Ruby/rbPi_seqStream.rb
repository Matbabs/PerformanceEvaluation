#!/usr/bin/ruby
require 'benchmark'

n, c = ARGF.gets.split(' ').map!(&:to_i)
p(Benchmark.realtime do
  # n = 1000000

  step = 1 / n.to_f

  sum = (1..n).map do |i|
    x = (i - 0.5) * step
    4.0 / (1.0 + x * x)
  end.reduce { |a, b| a + b }

  p sum * step
end)
