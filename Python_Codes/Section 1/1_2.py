R = 6200
C = 1* 10**-8
f_c = 1/(2*math.pi*R*C) #method of calculating the cutoff frequency for an RC circuit

print("Low pass filter")
print("===============")
print("Resistor: {} ohms".format(R))
print("Capacitor: {} farads".format(C))
print("Cutoff frequency: {} Hz".format(f_c))

low_cutoff = float(2567.0) 
lp_p2p_expected = 1/(np.sqrt(1+((np.array(freq)/(low_cutoff))**2)))

lp_freq_Vpp = {
    200: 1.3,
    400: 1.8, 
    600: 2.0, 
    1000: 2.2, 
    2000: 4.2,
    5000: 1.6
}
lp_freqs = sorted(list(lp_freq_Vpp.keys()))
lp_p2p_observed = [lp_freq_Vpp[f] for f in lp_freqs]

lp_gain_observed = np.array(lp_p2p_observed)/np.max(lp_p2p_observed)

plt.xlabel("Frequency (Hz)")
plt.ylabel("Output Voltage/Input Voltage")
plt.title("Frequency vs Gain (Low Pass)")
plt.plot(freq, lp_p2p_expected)
plt.scatter(lp_freqs, lp_gain_observed)
plt.show()

plt.xlabel("Frequency (Hz)")
plt.ylabel("Output Voltage/Input Voltage")
plt.title("log-Frequency vs log-Gain (Low Pass)")
plt.loglog(freq, lp_p2p_expected)
plt.scatter(lp_freqs, lp_gain_observed)
plt.show()