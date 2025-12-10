# this problem can be modelled as a Linear Programming problem
#
# we will check out this example:
#
# [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
# [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
# [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
#
# let xi be the number of times button i is pressed (1<=i<=n, xi>=0)
# each button contributes to one joltage, so lets write an equation 
# for each joltage (these are our constriants):
#
# 0x1 + 0x2 + 0x3 + 0x4 + 1x5 + 1x6 = 3;
#
# this means only buttons x5 and x6 contribute to the first joltage (3)
# repeat for every joltage, we get matrix A multiplied by vector x to get
# the joltage vector b;
# Ax = b;
#
# this could be a simple matrix equation if it were not for the objective
# of minimizing the button presses
#
# this means, under these constraints, were minimizing the sum of all xi,
# with the addition that xi are non-negative and INTEGERS (so this is a 
# Integer Linear Programming problem).
#
# so finally, the problem is formulated as such:
#
# arg min Z = x1 + x2 + ... + xn
# subject to
# Ax = b
#
# x1,x2,...,xn>=0, xi is INTEGER
#
# ADMISSION OF GUILT: I did not come up with this solution.
# I recently learned all about linear programming and completely
# understand this approach, but the idea came from reading the
# thinking logs of Claude Opus 4.5 when I told him to optimize
# my Dynamic Programming approach for this problem :)
using JuMP
using HiGHS

function solve_machine(buttons, target)
    num_counters = length(target)
    num_buttons = length(buttons)
    
    model = Model(HiGHS.Optimizer)
    set_silent(model)
    
    @variable(model, x[1:num_buttons] >= 0, Int)
    
    for c in 1:num_counters
        @constraint(model, sum(x[b] for b in 1:num_buttons if c in buttons[b]) == target[c])
    end
    
    @objective(model, Min, sum(x))
    
    optimize!(model)
    
    if termination_status(model) == MOI.OPTIMAL
        return Int(objective_value(model))
    else
        return -1
    end
end

function parse_input(filename)
    machines = []
    
    for line in eachline(filename)
        isempty(strip(line)) && continue
        
        button_matches = collect(eachmatch(r"\(([^)]+)\)", line))
        buttons = []
        for m in button_matches
            indices = parse.(Int, split(m.captures[1], ","))
            push!(buttons, indices .+ 1)  # Convert to 1-indexed
        end
        
        target_match = match(r"\{([^}]+)\}", line)
        target = parse.(Int, split(target_match.captures[1], ","))
        
        push!(machines, (buttons, target))
    end
    
    return machines
end

function main()
    machines = parse_input("input.txt")
    
    total = 0
    for (i, (buttons, target)) in enumerate(machines)
        result = solve_machine(buttons, target)
        println("Machine $i: $result")
        total += result
    end
    
    println("\nTotal: $total")
end

main()

