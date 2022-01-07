# ZZGrid

TL;DR: To try this out, build the source and run `zzGridTest` and open `/tmp/out.svg` in your favourite SVG viewer.

The Zig Zag-Grid, as known from railroad bridges, is defined by a few variables: Gw, Gh, Pt and N, as illustrated below, and a tolerance, T, the system need to be soved within. E.g. if units are in mm and T= 0.1, a match less than +/- 0.1mm for Gw is searched for.

```txt
┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐      ┬       ┬
│                                                                                                                                          │      │ Pt    │
│                                                                                                                                          │      │       │
└───────────────              ────────────────────────────────              ─────────────────────────────────              ────────────────┘      ┴       │      ┬
               /      /\      \                              /      /\      \                               /      /\      \                              │      │
              /      /  \      \                            /      /  \      \                             /      /  \      \                             │      │
             /      /    \      \                          /      /    \      \                           /      /    \      \                            │      │
            /      /      \      \                        /      /      \      \                         /      /      \      \                           │      │
           /      /        \      \                      /      /        \      \                       /      /        \      \                          │      │
          /      /          \      \                    /      /          \      \                     /      /          \      \                         │      │
         /      /            \      \                  /      /            \      \                   /      /            \      \                        │      │
        /      /              \      \                /      /              \      \                 /      /              \      \                       │      │
       /      /                \      \              /      /                \      \               /      /                \      \                      │ Gh   │ Tih (= Gh-2*Pt)
      /      /        1         \      \            /      /        2         \      \             /      /        N         \      \                     │      │
     /      /                    \      \          /      /                    \      \           /      /                    \      \                    │      │
    /      /                      \      \        /      /                      \      \         /      /                      \      \                   │      │
   /      /                        \      \      /      /                        \      \       /      /                        \      \                  │      │
  /      /                          \      \    /      /                          \      \     /      /                          \      \                 │      │
 /      /                            \      \  /      /                            \      \   /      /                            \      \                │      │
/      /  a                        a  \      \/      /                              \      \ /      /                              \      \               │      │
│      ────────────────────────────────              ────────────────────────────────               ────────────────────────────────       │      ┬       │      ┴
│                                                                                                                                          │      │ Pt    │
│                                                                                                                                          │      │       │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘      ┴       ┴
                                         /      /
                                        /      /
                                          Pt  /

├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
                                                           Gw

├────────────────────────────────────────────┤
                   Tw

      ├────────────────────────────────┤
                   Tiw

├─────┤
  Tww
```

so we need to determine an 'a' so that

```math
    | 
      N \cdot T_w(a, N, Pt, Gh, Gw)  - G_w 
    | 
    \le 
    T
```


To do so, we must define the formulas

```math
    T_w(a, N, Pt, Gh, Gw) 
```

```math
    T_{ww} = \frac{P_t}{sin(a)}
```

```math
  T_{iw} 
  = 
  2 \cdot \frac{T_{ih}}{tan(a)}
  = 
  2 \cdot \frac{G_h - 2 \cdot P_t}{tan(a)}
``` 

Tw  is then reachable as

```math
  T_w = 2 \cdot T_{ww} + T_{iw}
```


and a proper delta.
