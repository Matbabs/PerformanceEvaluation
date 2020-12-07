#!/usr/bin/ruby
#

rez = {}

ARGV.each do |filename|
  lines = File.new(filename, "r+").read.split("\n")

  # p filename
  # p destFile

  last_result = 10
  sum = 0
  nb_results = 0
  nb_threads = 1;

  filename = filename[0..-(File.extname(filename).length + 1)]
  theFile = File.new(filename+"_uniformized.csv", "w+")
  lines.each do |line|
    rez = line.split(";")
    if last_result != rez[0].to_i || nb_threads != rez[1].to_i
      moy = sum / nb_results
      theFile.write(''+last_result.to_s+';'+nb_threads.to_s+';'+moy.to_s+"\n")

      nb_results = 0
      last_result = rez[0].to_i
      nb_threads = rez[1].to_i
      sum = 0
    end

    nb_results+=1
    sum+=rez[2].to_f
  end

  moy = sum / nb_results
  theFile.write(''+last_result.to_s+';'+nb_threads.to_s+';'+moy.to_s+"\n")
end