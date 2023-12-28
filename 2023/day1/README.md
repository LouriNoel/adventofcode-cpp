# 2023 Day 1

The program of this day went through some refactoring.

`0` and `zero` do not appear in the input.

## Part 1

Beware of `treb7uchet`.

### Original Implementation

1. Parse each line into a list of digits (as strings) using regex
2. Concatenate the first digit with the last one (do not care if there is only one digit)
3. Convert to integer using `stoi` (the *calibration* value)
4. Sum them all

### Implementation n°2 (Optimization 1)

Do not use regex.

1. Parse each line into a list of digits by iterating through all characters and casting to integer
2. Compute the calibration with `10 * first + last` (do not care if there is only one digit)
3. Sum them all

Convert between `char` and `int` using `int i = ch - '0';`

### Implementation n°3 (Optimization 2)

Do not retrieve all the digits, but only the first and last one.

For each line:
1. Iterate from the beginning until a digit is found
2. Iterate from the end until a digit is found
3. Compute the calibration with `10 * first + last` (do not care if there is only one digit)
4. Add the calibration value to the sum of previously computed calibrations

### Implementation n°4 (C++11)

Do not write for-loops yourself.

Use `std::string::find_first_of` and `std::string::find_last_of` for searching any character in `"0123456789"`.

This is quicker to write, and less error-prone than a backward for-loop.

### Implementation n°5 (C++20)

Use `std::views` with `std::isdigit` for conciseness and to better describe the intent.

This gets rid of index-based access boilerplate: `int first = line[line.find_first_of("0123456789")] - '0';`  
But it takes a *tiny* bit longer to execute.

## Part 2

Beware of `oneight`.

### Original implementation

This implementation iterates 18 times over each line.

For each line:
1. For each token (1, ..., 9, one, ..., nine), find all the occurences in the line and remember their index
2. All tokens considered, select the first and the last one (by comparing their index)
3. Compute the calibration with `10 * first + last` (do not care if there is only one digit)
4. Add the calibration value to the sum of previously computed calibrations

### Implementation n°2

Use regex with a positive lookahead that only consumes 1 character when iterating over a line, which allows to match overlapping substrings.
```
(?=(\d|zero|one|two|three|four|five|six|seven|eight|nine)).
```
To retrieve the result, we must use a capturing group, otherwise we would only get the first character (the one which is consumed).

1. Parse each line into a list of digits (as strings) using regex, then map the strings onto their integer counterparts
2. Compute the calibration with `10 * first + last` (do not care if there is only one digit)
3. Sum them all

This only iterates once over each line... but being regex, it is slower anyway.  
I still keep it because I find it more elegant.

### Implementation n°3 (Optimization 1)

Still use regex, but only search for the first and the last match.
- do not forget that `std::regex_search` uses **const** iterators

This gets rid of the lookahead regex (which may be a little tricky to understand) and it also takes less time to execute.

But we must be clever to search *backwards*:
- `std::smatch` cannot be used when searching backwards, we must define it ourselves: `std::match_results<std::string::const_reverse_iterator>`
- another regex must be used when searching backwards : `\d|orez|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin`
- all these new candidates must be added to the map

Overall, I think it would have taken more time to write this solution instead of the "regex lookahead" one.  
Also, having to write `eerht` and the like is error-prone.
