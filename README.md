# ✅ miniRT Development Checklist

> This file tracks the requirements for the 42 Singapore miniRT project and breaks them into clear tasks. Check items off as you complete them.

---
## 📚 Useful Learning Resources

To understand ray tracing, here are some excellent learning resources:

- **Overview Article**: [Real-Time Ray Tracing Overview](https://www.realtimerendering.com/raytracing.html)
- **Video Series**: [NVIDIA’s Ray Tracing Essentials on YouTube](https://youtube.com/playlist?list=PLs59hM6wCkPnukQ6neBnbipvHOxOjOPoT&si=WD3jhuWwbIs6JpLn)
- **Online Guidebook**: [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview)


## 🧱 1. Project Setup

- [ ] Project written in C, follows Norm.
- [ ] Create `Makefile` with these rules: `all`, `clean`, `fclean`, `re`, `bonus`.
- [ ] Use only allowed functions: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`.
- [ ] Link `-lm` for `math.h` and use `MiniLibX`.
- [ ] Add `libft` as subfolder and link properly.

---

## 📄 2. .rt File Parsing

The program must read and parse a `.rt` file with the following requirements:

### General:
- [ ] `.rt` file must be passed as a command-line argument.
- [ ] Parse file ignoring blank lines and handling multiple spaces.
- [ ] Accept any order of elements.
- [ ] Only **1** of each: Ambient (A), Camera (C), Light (L).
- [ ] Validate ranges and format strictly.

### Required elements:
- [ ] **Ambient light** `A ratio R,G,B`  
  e.g. `A 0.2 255,255,255`
  - Ratio [0.0, 1.0]
  - RGB [0-255]

- [ ] **Camera** `C x,y,z orientation FOV`  
  e.g. `C -50.0,0,20 0,0,1 70`
  - FOV [0,180]
  - Orientation vector normalized [-1.0, 1.0]

- [ ] **Light** `L x,y,z brightness R,G,B`  
  e.g. `L -40,0,30 0.7 255,255,255`
  - Brightness ratio [0.0, 1.0]

### Object types:
- [ ] **Sphere** `sp x,y,z diameter R,G,B`  
- [ ] **Plane** `pl x,y,z normal R,G,B`  
- [ ] **Cylinder** `cy x,y,z orientation diameter height R,G,B`  

### Parser checks:
- [ ] Error on invalid/missing values
- [ ] Error on duplicate A, C, L
- [ ] Error message: `Error\n` + clear explanation

---

## 💡 3. Rendering Logic

- [ ] Implement ray casting engine
- [ ] Intersect functions:
  - [ ] Sphere
  - [ ] Plane
  - [ ] Cylinder
- [ ] Compute:
  - [ ] Ambient light
  - [ ] Diffuse light
  - [ ] Hard shadow

---

## 🎨 4. Image Display

- [ ] Set up window with MiniLibX
- [ ] Draw rendered image
- [ ] Handle:
  - [ ] ESC key to quit
  - [ ] Red cross to quit
- [ ] Make sure app is responsive

---

## 🧹 5. Error Handling & Memory

- [ ] Exit cleanly on bad input
- [ ] Free all memory properly
- [ ] No memory leaks
- [ ] Handle null pointers, malloc fails

---

## 🧪 6. Testing

- [ ] Add `.rt` test files to `scenes/`
- [ ] Test edge cases (e.g. zero FOV, bad RGB)
- [ ] Check performance/responsiveness
- [ ] Confirm Norm compliance

---

## ✨ 7. Bonus Ideas (Optional)

Only add these **after** the mandatory part is 100% working.

- [ ] Phong specular reflection
- [ ] Checkerboard pattern
- [ ] Colored multi-lights
- [ ] New shapes (cone, paraboloid)
- [ ] Bump mapping
- [ ] Textures or skybox
- [ ] Mouse/camera movement

---

## 📦 Repo Structure

```bash
miniRT/
├── src/
├── include/
├── scenes/
│   └── test_scene.rt
├── libft/
├── ft_gnl
├── mlx/
├── Makefile
├── README.md
