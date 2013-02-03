module WordGolf
  class Board
    def initialize()
      @board = []
      @scores = Array.new(0)
      print "what now? >  "
    end

    def set(x = 5, y = 5)
      @counts = Hash.new(0)
      alphabet = ("a".."z").to_a
      (0..y-1).each do |n|
        @board[n] = []
        x.times do
          @board[n] << alphabet[rand(25)]
          @counts[@board[n].last] += 1
        end
      end
      puts "A new #{x} by #{y} board has been started!"
    end

    def display
      output = "\n"
      @board.each do |y|
        output += y.join('  ') + "\n"
      end
      puts output, "\n"
    end

    def play_word(word)
      word.downcase!
      if validate(word)
        word.each_char do |char|
          @counts[char] -= 1
          @board.each do |row|
            if row.include?(char)
              row[row.index(char)] = ' '
              break
            end
          end
        end
        puts "You can play that word!"
      else
        puts "Um, that word doesn't work..."
      end
      display
    end

    def validate(word)
      counts = Hash.new(0)
      word.each_char do |char|
        counts[char] += 1
      end
      counts.each do |letter, count|
        return false unless @counts[letter] >= count
      end
      return true
    end

    def forfeit
      @scores << @counts.values.inject(:+)
      puts "Game\tScore"
      @scores.each_with_index.each do |score, index|
        puts "#{index + 1}\t#{score}"
      end
      puts "You have ended game #{@scores.length} with a score of #{@scores.last} for a total of #{@scores.inject(:+)}"
      if @scores.count > 8
        puts "Game Over"
        exit
      end
    end
  end
end

puts "#new -> new game\n#end -> stop and score game\n#next -> play the next round.\n"
board = WordGolf::Board.new

$stdin.each do |line|
  puts "#new -> new game\n#end -> stop and score game\n#next -> play the next round.\n"
  puts "\n"
  if line[0] == '#'
    case line[1..-2]
    when 'new'
      board.set
      board.display
      print "pick a word >  "
    when 'next'
      board.forfeit
      board.set
      board.display
      print "pick a word >  "
    when'end'
      board.forfeit
      exit
    end
  else
    board.play_word(line.chomp)
    print "pick a word >  "
  end
end
