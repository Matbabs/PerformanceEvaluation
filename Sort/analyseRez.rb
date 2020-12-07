#!/usr/bin/ruby
#

rez = {}

filename = ARGV[0]
destFile = ARGV[1]

lines = File.new(filename, "r+").read.split("\n\n")

# p filename
# p destFile
# p lines

theFile = File.new(destFile, "w+")
lines.each do |line|
  rez = line.split("\n")
  theFile.write(''+rez[0]+';'+rez[1]+';'+rez[2]+"\n")
end


