# 🌳 Family Tree Communication Problem

This project solves a two-part problem related to constructing a **binary family tree**, distributing **phones** efficiently, and analyzing **communication compatibility** between phones based on **prime values** and **XOR ranges**.

---

## 🧩 Subtask 1 — Minimum Phones Required

### 🧠 Problem Description
You are given the **level-order traversal** of a binary tree as an array `level_order` consisting of `1`s and `0`s:
- `1` → A valid family member (node exists)
- `0` → No member (null node)

You need to:
1. Construct the binary tree.
2. Determine the **minimum number of phones** that must be distributed among members such that:
   - Every member is either given a phone, or
   - Is covered by a phone of their **parent** or **child**.
   - A member **without** a phone can only **be shared with**, not share further.

This is analogous to the **Binary Tree Camera** problem.

### 📥 Input Format
n

level_order[0] level_order[1] ... level_order[n-1]

### 📤 Output Format
m

Where `m` = minimum number of phones required.


### 🧠 Approach
- Construct the tree using level-order traversal.
- Perform **post-order DFS traversal** to decide where phones are needed:
  - `0`: Node needs a phone.
  - `1`: Node has a phone.
  - `2`: Node is covered.
- Count total phones assigned
## 🔌 Subtask 2 — Out-of-Range Phone Pairs

### 📝 Problem Statement

After determining the number of phones `m` from **Subtask 1**,  
you are told that each of these `m` phones has a **unique prime value**:
- The *i-th* phone’s prime value = *i-th smallest prime number*.

Astroworld allows communication between phones **only if**  
the XOR of their prime values lies within the range `[l, r]`.

Your task is to find the number of phone pairs **whose XOR lies outside this range**.

### 🔢 Input Format
n

level_order[0] level_order[1] ... level_order[n-1]

l r


### 🧮 Output Format
m

x

### ⚙️ Constraints
- `1 ≤ n ≤ 3e5`
- `level_order[i] ∈ {0, 1}`
- `0 ≤ l ≤ r ≤ 2e6`
where:
- `m` = minimum number of phones (from Subtask 1)
- `x` = number of **out-of-range** phone pairs


