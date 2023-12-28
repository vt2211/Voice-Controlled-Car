f_values = {
    "marginally stable": (-0.3, 0.3),
    "stable, corrects error in one step": (0.5, 0.5),
    "oscillatory, marginally stable": (1, 1),
    "oscillatory, unstable": (1.1, 1.1),
    "stable": (0.2, 0.2),
}

for key in f_values:
    f_left, f_right = f_values[key]

    titles = ["Closed-loop control with perfect model",
              "Closed-loop control with model mismatch, fL={}, fR={}".format(f_left, f_right)]
    _, delta = utils.two_sims(titles, simulator, v_star, drive_straight_left_cl, drive_straight_right_cl)

    print("fL={}, fR={}".format(f_left, f_right))
    print("Eigenvalue of system: 1-fL-fR={:.2g}; {}".format(1-f_left-f_right, key))
    plt.show()
    steady_state_error = delta[-1]


f_left, f_right = .9, .9 

print("fL={}, fR={}".format(f_left, f_right))
print("Eigenvalue of system: 1-fL-fR={:.2g}; {}".format(1-f_left-f_right, key))
plt.show()
steady_state_error = delta[-1]