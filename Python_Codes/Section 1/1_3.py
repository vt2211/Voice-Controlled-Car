R = 51
L = 0.0033
C = 0.000001
f_c = 1/(2*math.pi*math.sqrt(L*C)) #method of calculating the cutoff frequency for an LRC circuit

print("Notch filter")
print("================")
print("Resistor: {} ohms".format(R))
print("Inductor: {} henries".format(L))
print("Capacitor: {} farads".format(C))
print("Notch frequency: {} Hz".format(f_c))

notch_freq = float(2771)
notch_p2p_expected = np.abs(np.array(freq)-notch_freq**2/np.array(freq))/(np.sqrt((R/L)**2 + (np.array(freq)-notch_freq**2/np.array(freq))**2))

notch_freq_Vpp = {
    1000: 1.6,
    2000: 2.4,
    2500: 1.5,
    3000: 1.2,
    5000: 1.4,
    7000: 2.2
}
notch_freqs = sorted(list(notch_freq_Vpp.keys()))
notch_p2p_observed = [notch_freq_Vpp[f] for f in notch_freqs]

notch_gain_observed = np.array(notch_p2p_observed)/np.max(notch_p2p_observed)

plt.xlabel("Frequency (Hz)")
plt.ylabel("Output Voltage/Input Voltage")
plt.title("Frequency vs Gain (Notch)")
plt.plot(freq, notch_p2p_expected)
plt.scatter(notch_freqs, notch_gain_observed)
plt.show()

plt.xlabel("Frequency (Hz)")
plt.ylabel("Output Voltage/Input Voltage")
plt.title("log-Frequency vs log-Gain (Notch)")
plt.loglog(freq, notch_p2p_expected)
plt.scatter(notch_freqs, notch_gain_observed)
plt.show()