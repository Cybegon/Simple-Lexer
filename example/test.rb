require 'fileutils'

OWN_DIR = File.absolute_path File.dirname(__FILE__)

Dir.glob(File.join(OWN_DIR, '*.webp')).each do |fn|
    fn_base = File.basename(fn, '.*')
    fn_new = "#{fn_base}.jpeg"

    if not system('sips', '-s', 'format', 'jpeg', 
                  '-s', 'formatOptions', 'normal', 
                  fn, '--out', fn_new)
        STDERR.puts("Failed! Aborting...")
        exit 1
    end

    FileUtils.rm fn
end

hello = :yes
case hello
when :yes
  puts "world"
when :tsar
  puts "goodbye."
else
  puts "no"
end

if hello == :yes then
  puts "world"
elsif hello == :tsar
  puts "goodbye."
else
  puts "no"
end