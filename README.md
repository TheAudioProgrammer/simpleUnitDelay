# simpleUnitDelay

This Unit delay is based off concepts from Will Pirkle's "Designing Audio Effect Plugins in C++" pages 58-63, which I have adapted to the Juce Framework here.

The most simple filter that can be implemented in dsp is the unit delay, using the equation y(n) = (a0 * xn) + (a1 * x(n - 1))

where:
a0 and a1 are coefficients

0.0 <= a1 <= 0.49
a0 = a1 - 1.0

xn is the current input sample
x(n-1) is the input sample from time n - 1



