#!/usr/bin/ruby
require 'benchmark'

n, c = ARGF.gets.split(' ').map!(&:to_i)
arr = []
step = 1 / n.to_f
tot = 0.0
div = n / c

p(Benchmark.realtime do
  (c).times do |i|
    arr[i] = Thread.new {
      start = (i * div).to_i
      stop = ((i+1) * div).to_i
      # p i, start, stop
      sum = 0.0
      (start..stop-1).each do |j|
        x = (j - 0.5) * step
        sum += 4.0 / (1.0 + x * x)
      end

      Thread.current["mycount"] = sum
    }
  end

  arr.each {|t| t.join; tot += t["mycount"]}
  p tot*step

end )
