export function remap(a1, a2, b1, b2, a) {
  return (a - a1) / (a2 - a1) * (b2 - b1) + b1;
}
