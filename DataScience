import matplotlib.pyplot as plt
import pandas as pd

# Load the combined data
df_combined = pd.read_csv('combined_data23.csv')

# Convert 'Date' and 'Time' columns to datetime format
df_combined['Date'] = pd.to_datetime(df_combined['Date'], format='%d/%m/%Y')
df_combined['Time'] = pd.to_datetime(df_combined['Time'], format='%H:%M:%S')

# Combine date and time into a new 'DateTime' column
df_combined['DateTime'] = df_combined['Date'].dt.strftime('%d/%m/%Y') + ' ' + df_combined['Time'].dt.strftime('%H:%M:%S')

# Function to plot lines while skipping segments with more than 20 missing values
def plot_with_gap(df, x, y, label, color):
    # Replace NaN with a marker to indicate gaps
    mask = df[y].notna()

    # Plot the line ignoring missing values
    plt.plot(df[x][mask], df[y][mask], label=label, color=color)

# Function to detect and mark temperature drops greater than 5 degrees
def add_vertical_lines_for_drops(df, temp_column):
    for i in range(1, len(df)):
        if pd.notna(df[temp_column].iloc[i]) and pd.notna(df[temp_column].iloc[i-4]):
            if abs(df[temp_column].iloc[i] - df[temp_column].iloc[i-4]) > 5:
                # Add a vertical line where the temperature drops more than 5 degrees
                plt.axvline(x=df['DateTime'].iloc[i], color='red', linestyle='--', lw=1)

# Create a figure for indoor and outdoor temperature and humidity
plt.figure(figsize=(12, 6))

# Plot indoor temperature
plot_with_gap(df_combined, 'DateTime', 'Temperature_Inside', 'Indoor Temperature', 'blue')

# Plot indoor humidity
plot_with_gap(df_combined, 'DateTime', 'Humidity_Inside', 'Indoor Humidity', 'green')

# Plot outdoor temperature
plot_with_gap(df_combined, 'DateTime', 'Temperature_Outside', 'Outdoor Temperature', 'red')

# Plot outdoor humidity
plot_with_gap(df_combined, 'DateTime', 'Humidity_Outside', 'Outdoor Humidity', 'orange')

# Add vertical lines where the indoor temperature drops more than 5 degrees
add_vertical_lines_for_drops(df_combined, 'Temperature_Inside')

# Add labels and title
plt.xlabel('Date and Time')
plt.ylabel('Values')
plt.title('Indoor and Outdoor Temperature and Humidity')

# Show ticks every 50 data points
plt.xticks(df_combined['DateTime'][::50], rotation=45)

# Add legend and grid
plt.legend(loc='best')
plt.grid(True)

# Adjust spacing and display the plot
plt.tight_layout()
plt.show()
