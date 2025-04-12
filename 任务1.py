from itertools import permutations

data = [
    "fnd17_oxlcxspebq", "fnd17_shsoutbs", "fnd28_value_05191q", "fnd28_value_05301q",
    "fnd28_value_05302q", "fnd17_pehigh", "fnd17_pelow", "fnd17_priceavg150day",
    "fnd17_priceavg200day", "fnd17_priceavg50day", "fnd17_pxedra", "fnd28_newa3_value_18191a",
    "fnd28_value_02300a", "mdl175_ebitda", "mdl175_pain"
]

formulas = [
    f"ts_regression(ts_zscore({A}, 500), ts_zscore({B}, 500), 500)"
    for A, B in permutations(data, 2)
]

for formula in formulas:
    print(formula)

print(f"\nTotal number of combinations: {len(formulas)}")