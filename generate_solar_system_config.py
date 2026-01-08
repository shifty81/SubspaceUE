#!/usr/bin/env python3
"""
Solar System Configuration Generator
Generates configuration data and helper information for the Sol Testing Grounds
"""

import math
import json

# Real-world planetary data
PLANETS = [
    {
        "name": "Mercury",
        "semi_major_axis_au": 0.38709893,
        "eccentricity": 0.20563069,
        "orbital_period_days": 87.969,
        "inclination_deg": 7.00487,
        "longitude_ascending_node_deg": 48.33167,
        "argument_periapsis_deg": 77.45645,
        "mean_anomaly_epoch_deg": 252.25084,
        "diameter_km": 4879.4,
        "mass_earth_masses": 0.0553,
        "rotation_period_days": 58.646,
        "has_moons": False
    },
    {
        "name": "Venus",
        "semi_major_axis_au": 0.72333199,
        "eccentricity": 0.00677323,
        "orbital_period_days": 224.701,
        "inclination_deg": 3.39471,
        "longitude_ascending_node_deg": 76.68069,
        "argument_periapsis_deg": 131.53298,
        "mean_anomaly_epoch_deg": 181.97973,
        "diameter_km": 12103.6,
        "mass_earth_masses": 0.815,
        "rotation_period_days": 243.018,
        "has_moons": False
    },
    {
        "name": "Earth",
        "semi_major_axis_au": 1.00000011,
        "eccentricity": 0.01671022,
        "orbital_period_days": 365.256,
        "inclination_deg": 0.00005,
        "longitude_ascending_node_deg": -11.26064,
        "argument_periapsis_deg": 102.94719,
        "mean_anomaly_epoch_deg": 100.46435,
        "diameter_km": 12742.0,
        "mass_earth_masses": 1.0,
        "rotation_period_days": 1.0,
        "has_moons": True
    },
    {
        "name": "Mars",
        "semi_major_axis_au": 1.52366231,
        "eccentricity": 0.09341233,
        "orbital_period_days": 686.980,
        "inclination_deg": 1.85061,
        "longitude_ascending_node_deg": 49.57854,
        "argument_periapsis_deg": 336.04084,
        "mean_anomaly_epoch_deg": 355.45332,
        "diameter_km": 6779.0,
        "mass_earth_masses": 0.107,
        "rotation_period_days": 1.026,
        "has_moons": True
    },
    {
        "name": "Jupiter",
        "semi_major_axis_au": 5.20336301,
        "eccentricity": 0.04839266,
        "orbital_period_days": 4332.589,
        "inclination_deg": 1.30530,
        "longitude_ascending_node_deg": 100.55615,
        "argument_periapsis_deg": 14.75385,
        "mean_anomaly_epoch_deg": 34.40438,
        "diameter_km": 139820.0,
        "mass_earth_masses": 317.8,
        "rotation_period_days": 0.414,
        "has_moons": True
    },
    {
        "name": "Saturn",
        "semi_major_axis_au": 9.53707032,
        "eccentricity": 0.05415060,
        "orbital_period_days": 10759.22,
        "inclination_deg": 2.48446,
        "longitude_ascending_node_deg": 113.71504,
        "argument_periapsis_deg": 92.43194,
        "mean_anomaly_epoch_deg": 49.94432,
        "diameter_km": 116460.0,
        "mass_earth_masses": 95.2,
        "rotation_period_days": 0.444,
        "has_moons": True
    },
    {
        "name": "Uranus",
        "semi_major_axis_au": 19.19126393,
        "eccentricity": 0.04716771,
        "orbital_period_days": 30688.5,
        "inclination_deg": 0.76986,
        "longitude_ascending_node_deg": 74.22988,
        "argument_periapsis_deg": 170.96424,
        "mean_anomaly_epoch_deg": 313.23218,
        "diameter_km": 50724.0,
        "mass_earth_masses": 14.5,
        "rotation_period_days": 0.718,
        "has_moons": True
    },
    {
        "name": "Neptune",
        "semi_major_axis_au": 30.06896348,
        "eccentricity": 0.00858587,
        "orbital_period_days": 60182.0,
        "inclination_deg": 1.76917,
        "longitude_ascending_node_deg": 131.72169,
        "argument_periapsis_deg": 44.97135,
        "mean_anomaly_epoch_deg": 304.88003,
        "diameter_km": 49244.0,
        "mass_earth_masses": 17.1,
        "rotation_period_days": 0.671,
        "has_moons": True
    }
]

# Constants
AU_TO_KM = 149597870.7
CM_PER_KM = 100000.0

def calculate_scaled_values(distance_scale=0.00001, size_scale=50.0, time_multiplier=10000.0):
    """Calculate scaled values for Unreal Engine"""
    print("\n" + "="*80)
    print(f"SOLAR SYSTEM SCALE CALCULATIONS")
    print(f"Distance Scale: 1:{int(1/distance_scale):,}")
    print(f"Planet Size Scale: {size_scale}x")
    print(f"Time Multiplier: {time_multiplier}x")
    print("="*80 + "\n")
    
    results = []
    
    for planet in PLANETS:
        # Calculate distances
        distance_km = planet["semi_major_axis_au"] * AU_TO_KM
        distance_uu = distance_km * CM_PER_KM * distance_scale
        
        # Calculate sizes
        radius_km = planet["diameter_km"] / 2.0
        radius_uu = radius_km * CM_PER_KM * size_scale
        
        # Calculate orbit times with multiplier
        real_orbit_days = planet["orbital_period_days"]
        real_orbit_seconds = real_orbit_days * 86400.0
        scaled_orbit_seconds = real_orbit_seconds / time_multiplier
        scaled_orbit_minutes = scaled_orbit_seconds / 60.0
        scaled_orbit_hours = scaled_orbit_minutes / 60.0
        
        result = {
            "name": planet["name"],
            "distance_au": planet["semi_major_axis_au"],
            "distance_km": distance_km,
            "distance_uu": distance_uu,
            "distance_game_km": distance_uu / CM_PER_KM,
            "radius_real_km": radius_km,
            "radius_uu": radius_uu,
            "radius_game_km": radius_uu / CM_PER_KM,
            "orbit_real_days": real_orbit_days,
            "orbit_scaled_seconds": scaled_orbit_seconds,
            "orbit_scaled_minutes": scaled_orbit_minutes,
            "orbit_scaled_hours": scaled_orbit_hours
        }
        
        results.append(result)
        
        # Print readable output
        print(f"{planet['name']}:")
        print(f"  Real Distance: {planet['semi_major_axis_au']:.3f} AU ({distance_km:,.0f} km)")
        print(f"  Game Distance: {result['distance_game_km']:,.0f} km ({distance_uu:,.0f} UU)")
        print(f"  Real Radius: {radius_km:,.0f} km")
        print(f"  Game Radius: {result['radius_game_km']:,.1f} km ({radius_uu:,.0f} UU)")
        print(f"  Real Orbit: {real_orbit_days:.1f} days")
        
        if scaled_orbit_hours > 24:
            print(f"  Game Orbit: {scaled_orbit_hours/24:.1f} days ({scaled_orbit_hours:.1f} hours)")
        elif scaled_orbit_hours > 1:
            print(f"  Game Orbit: {scaled_orbit_hours:.1f} hours ({scaled_orbit_minutes:.0f} minutes)")
        else:
            print(f"  Game Orbit: {scaled_orbit_minutes:.1f} minutes ({scaled_orbit_seconds:.0f} seconds)")
        print()
    
    return results

def generate_blueprint_csv(distance_scale=0.00001, size_scale=50.0):
    """Generate CSV for easy import to Blueprint/Excel"""
    print("\n" + "="*80)
    print("CSV FORMAT FOR BLUEPRINT IMPORT")
    print("="*80 + "\n")
    
    print("PlanetName,SemiMajorAxisUU,Eccentricity,OrbitalPeriodDays,InclinationDeg,LongAscNodeDeg,ArgPeriapsisDeg,MeanAnomalyDeg,DiameterKm,MassEarthMasses,RotationPeriodDays,HasMoons")
    
    for planet in PLANETS:
        distance_km = planet["semi_major_axis_au"] * AU_TO_KM
        distance_uu = distance_km * CM_PER_KM * distance_scale
        
        print(f"{planet['name']},{distance_uu:.2f},{planet['eccentricity']:.8f},"
              f"{planet['orbital_period_days']:.3f},{planet['inclination_deg']:.5f},"
              f"{planet['longitude_ascending_node_deg']:.5f},"
              f"{planet['argument_periapsis_deg']:.5f},"
              f"{planet['mean_anomaly_epoch_deg']:.5f},{planet['diameter_km']:.1f},"
              f"{planet['mass_earth_masses']:.3f},{planet['rotation_period_days']:.3f},"
              f"{'TRUE' if planet['has_moons'] else 'FALSE'}")

def calculate_camera_distances():
    """Calculate recommended camera distances for viewing planets"""
    print("\n" + "="*80)
    print("RECOMMENDED CAMERA DISTANCES")
    print("="*80 + "\n")
    
    distance_scale = 0.00001
    size_scale = 50.0
    
    for planet in PLANETS:
        radius_km = planet["diameter_km"] / 2.0
        radius_uu = radius_km * CM_PER_KM * size_scale
        
        # Good viewing distance is roughly 3-5x planet radius
        min_distance = radius_uu * 3
        max_distance = radius_uu * 5
        
        print(f"{planet['name']}:")
        print(f"  Planet Radius: {radius_uu:,.0f} UU")
        print(f"  Min View Distance: {min_distance:,.0f} UU ({min_distance/CM_PER_KM:,.0f} km)")
        print(f"  Max View Distance: {max_distance:,.0f} UU ({max_distance/CM_PER_KM:,.0f} km)")
        print()

def export_json_config(filename="solar_system_config.json"):
    """Export configuration as JSON"""
    config = {
        "version": "1.0",
        "date_created": "2026-01-08",
        "scale_factors": {
            "distance_scale": 0.00001,
            "planet_size_scale": 50.0,
            "default_time_multiplier": 10000.0
        },
        "constants": {
            "au_to_km": AU_TO_KM,
            "cm_per_km": CM_PER_KM,
            "sun_diameter_km": 1392700.0
        },
        "planets": PLANETS
    }
    
    with open(filename, 'w') as f:
        json.dump(config, f, indent=2)
    
    print(f"\n✓ Exported configuration to {filename}")

def main():
    """Main entry point"""
    print("\n" + "="*80)
    print("SOL TESTING GROUNDS - CONFIGURATION GENERATOR")
    print("="*80)
    
    # Calculate and display scaled values
    results = calculate_scaled_values(
        distance_scale=0.00001,
        size_scale=50.0,
        time_multiplier=10000.0
    )
    
    # Generate CSV for easy reference
    generate_blueprint_csv()
    
    # Calculate camera distances
    calculate_camera_distances()
    
    # Export JSON config
    export_json_config()
    
    print("\n" + "="*80)
    print("Generation Complete!")
    print("="*80 + "\n")

if __name__ == "__main__":
    main()
