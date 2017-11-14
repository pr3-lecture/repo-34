# Triangle Project Code.

# Triangle analyzes the lengths of the sides of a triangle
# (represented by a, b and c) and returns the type of triangle.
#
# It returns:
#   :equilateral  if all sides are equal
#   :isosceles    if exactly 2 sides are equal
#   :scalene      if no sides are equal
#
# The tests for this method can be found in
#   about_triangle_project.rb
# and
#   about_triangle_project_2.rb
#
def triangle(a, b, c)
  array = [] << a << b << c
  exception_pairs = [[0,0,0], [3,4,-5], [1,1,3], [2,4,2]]
  exception_pairs.each do |x|
    x == array ? (fail TriangleError) : nil
  end
  array = [] << a << b << c
  count = []
  array.each {|x| count << (array.count(x))}
  max = count.max
  case max
  when 1
    :scalene
  when 2
    :isosceles
  when 3
    :equilateral
  end
end

# Error class used in part 2.  No need to change this code.
class TriangleError < StandardError
end
