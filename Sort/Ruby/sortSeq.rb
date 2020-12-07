#!/usr/bin/ruby
require 'benchmark'

N = ARGV[0].to_i

p(Benchmark.realtime do
  Array.new(N) { rand(0..N) }.sort!
end)
