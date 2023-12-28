plt.figure(figsize=(5, 7))
plt.subplot(211)
# Simulate using steady_state_error
d = simulator.simulate(
    v_star, drive_straight_left_cl, drive_straight_right_cl, mismatch_error=0.1, sim_length=20, offset=steady_state_error)
delta = simulator.plot(d)
plt.title("Closed-loop control with model mismatch and\nsteady state error correction, fL={}, fR={}"
          .format(f_left, f_right))
plt.subplot(212)
plt.plot(delta, 'r')
plt.ylabel('delta')
plt.xlabel('n(sample)')
plt.grid()