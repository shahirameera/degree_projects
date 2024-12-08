library(shiny)
library(shinydashboard)
library(tidyverse)
library(plotly)
library(anytime)
library(ggplot2)
library(dplyr)
library(tidyr)
library(janitor)
library(shinythemes)
library(readr)
library(DT)
library(viridis)

# Load and clean the data
data <- read_csv("C:/Users/andy0/OneDrive/Desktop/DSP 2/COVID-19 and Its Impact On Students Mental Health.csv") %>%
  clean_names() %>%
  rename(Region = region_of_residence)

# Rename columns for easier referencing
colnames(data) <- c("ID", "Region", "Age", "OnlineClassHours", "OnlineClassRating", 
                    "OnlineClassMedium", "SelfStudyHours", "FitnessHours", "SleepHours", 
                    "SocialMediaHours", "SocialMediaPlatform", "TVHours", 
                    "MealsPerDay", "WeightChange", "HealthIssue", "StressBuster", 
                    "TimeUtilized", "FeelCloser", "MissMost")

# Create age range categories
data <- data %>%
  mutate(AgeRange = cut(Age, breaks = c(5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60),
                        labels = c("5-10", "11-15", "16-20", "21-25", "26-30", "31-35", "36-40", "41-45", "46-50", "51-55", "56-60")))

# Aggregate the data for good and bad things
data <- data %>%
  mutate(GoodThings = SelfStudyHours + FitnessHours + SleepHours,
         BadThings = SocialMediaHours + TVHours)

# UI for the Shiny app
ui <- dashboardPage(
  dashboardHeader(title = "COVID-19 Analysis"),
  dashboardSidebar(
    sidebarMenu(
      menuItem("Main Tab", tabName = "cover", icon = icon("book")),
      menuItem("Average Time Spent (Activities)", tabName = "time_activities", icon = icon("chart-bar")),
      menuItem("Sleep Impact", tabName = "sleep_impact", icon = icon("bed")),
      menuItem("Rating Vs. Time Spent Online", tabName = "online_class", icon = icon("laptop")),
      menuItem("Health Issues", tabName = "health_issues", icon = icon("heart")),
      menuItem("Weight Change", tabName = "weight_change", icon = icon("weight-hanging")),
      menuItem("Time Spent (Online Class)", tabName = "scatter_plot", icon = icon("chart-line")),  # Changed icon to chart-line
      menuItem("Preferred Social Media", tabName = "social_media", icon = icon("users")),
      menuItem("Good vs. Bad Habits", tabName = "good_bad", icon = icon("hourglass"))
    )
  ),
  dashboardBody(
    tabItems(
      tabItem(
        tabName = "cover",
        h1("Welcome to COVID-19 Analysis Dashboard"),
        p("This dashboard provides insights into the impact of COVID-19 on students' mental health."),
        tags$img(src = "Image for dashboard.jpg", height = 560, width = 1200),
        p("Click on the sidebar menu to explore different sections of the analysis.")
      ),
      tabItem(
        tabName = "time_activities",
        plotlyOutput("plot_time_activities")
      ),
      tabItem(
        tabName = "sleep_impact",
        plotlyOutput("plot_sleep_impact")
      ),
      tabItem(
        tabName = "online_class",
        plotlyOutput("plot_online_class")
      ),
      tabItem(
        tabName = "health_issues",
        plotlyOutput("plot_health_issues")
      ),
      tabItem(
        tabName = "weight_change",
        plotlyOutput("plot_weight_change")
      ),
      tabItem(
        tabName = "scatter_plot",
        plotOutput("plot_scatter"),
        selectInput("region", "Select Region", choices = c("All Regions", unique(data$Region)), selected = "All Regions"),
        selectInput("activity", "Select Activity", choices = c("Online Class" = "OnlineClassHours", "Self Study" = "SelfStudyHours", "Fitness" = "FitnessHours", "Sleep" = "SleepHours", "Social Media" = "SocialMediaHours", "TV" = "TVHours"), selected = "OnlineClassHours"),
        sliderInput("slider", "Age Range", min = min(data$Age, na.rm = TRUE), max = max(data$Age, na.rm = TRUE), value = c(min(data$Age, na.rm = TRUE), max(data$Age, na.rm = TRUE)))
      ),
      tabItem(
        tabName = "social_media",
        plotOutput("plot_social_media"),
        selectInput("region_social", "Select Region", choices = c("All Regions", unique(data$Region)), selected = "All Regions"),
        selectInput("social_media", "Select Social Media", choices = c("All", unique(data$SocialMediaPlatform)), selected = "All")
      ),
      tabItem(
        tabName = "good_bad",
        plotOutput("plot_good_bad")
      )
    )
  )
)

# Server logic
server <- function(input, output) {
  output$plot_time_activities <- renderPlotly({
    data_long <- data %>%
      select(OnlineClassHours, SelfStudyHours, FitnessHours, SleepHours, SocialMediaHours, TVHours) %>%
      pivot_longer(cols = everything(), names_to = "Activity", values_to = "Hours")
    
    p <- ggplot(data_long, aes(x = Activity, y = Hours, fill = Activity)) +
      geom_bar(stat = "summary", fun = "mean") +
      labs(title = "Average Time Spent on Different Activities and Gadgets", x = "Activity", y = "Average Hours") +
      theme_minimal() +
      scale_fill_brewer(palette = "Set3")
    
    ggplotly(p)
  })
  
  output$plot_sleep_impact <- renderPlotly({
    p <- ggplot(data, aes(x = SocialMediaHours + TVHours, y = SleepHours)) +
      geom_point(alpha = 0.6) +
      labs(title = "Impact of Social Media and TV on Sleep Hours", x = "Time Spent on Social Media and TV (Hours)", y = "Sleep Hours") +
      theme_minimal()
    
    ggplotly(p)
  })
  
  output$plot_online_class <- renderPlotly({
    p <- ggplot(data, aes(x = factor(OnlineClassRating), y = OnlineClassHours, fill = factor(OnlineClassRating))) +
      geom_boxplot() +
      labs(title = "Online Class Rating vs. Time Spent Online", x = "Online Class Rating", y = "Time Spent Online (Hours)") +
      theme_minimal() +
      scale_fill_brewer(palette = "Set2")
    
    ggplotly(p)
  })
  
  output$plot_health_issues <- renderPlotly({
    filtered_data <- data %>% filter(HealthIssue == "YES")
    
    p <- ggplot(filtered_data, aes(x = Age, fill = HealthIssue)) +
      geom_histogram(binwidth = 2, position = "dodge") +
      labs(title = "Age Distribution for Health Issues (Yes)", x = "Age", y = "Count", fill = "Health Issue") +
      theme_minimal()
    
    ggplotly(p)
  })
  
  output$plot_weight_change <- renderPlotly({
    p <- ggplot(data, aes(x = HealthIssue, y = WeightChange, fill = HealthIssue)) +
      geom_bar(stat = "summary", fun = "mean", position = "dodge") +
      labs(title = "Average Change in Weight by Health Issues", x = "Health Issue", y = "Average Weight Change") +
      theme_minimal() +
      scale_fill_brewer(palette = "Pastel1")
    
    ggplotly(p)
  })
  
  output$plot_scatter <- renderPlot({
    scatter_plot(data = data, activity = input$activity, min_age = input$slider[1], max_age = input$slider[2], region = input$region)
  })
  
  # Reactive expression to filter data based on selected region and social media platform for social media plot
  filtered_data_social <- reactive({
    if (input$region_social == "All Regions" & input$social_media == "All") {
      data
    } else if (input$region_social == "All Regions") {
      data %>% filter(SocialMediaPlatform == input$social_media)
    } else if (input$social_media == "All") {
      data %>% filter(Region == input$region_social)
    } else {
      data %>% filter(Region == input$region_social, SocialMediaPlatform == input$social_media)
    }
  })
  
  output$plot_social_media <- renderPlot({
    filtered_data <- filtered_data_social()
    ggplot(filtered_data, aes(x = SocialMediaPlatform, y = Age, color = SocialMediaPlatform)) +
      geom_boxplot(outlier.colour = "red", outlier.shape = 16, outlier.size = 2, lwd = 0.5) +
      labs(
        title = "Preferred Social Media by Region and Age",
        x = "Social Media Platform",
        y = "Age"
      ) +
      theme_minimal() +
      scale_color_viridis(discrete = TRUE)
  })
  
  output$plot_good_bad <- renderPlot({
    good_bad_data <- data %>%
      group_by(AgeRange) %>%
      summarize(
        MeanGood = mean(GoodThings, na.rm = TRUE),
        MeanBad = mean(BadThings, na.rm = TRUE)
      ) %>%
      pivot_longer(cols = c("MeanGood", "MeanBad"), names_to = "Type", values_to = "MeanHours")
    
    ggplot(good_bad_data, aes(x = AgeRange, y = MeanHours, fill = Type)) +
      geom_bar(stat = "identity", position = "dodge") +
      labs(
        title = "Comparison of Good vs. Bad Habits by Age Range",
        x = "Age Range",
        y = "Average Hours",
        fill = "Habit Type"
      ) +
      theme_minimal()
  })
}

# Function to create scatter plots based on user input
scatter_plot <- function(data, activity, min_age, max_age, region) {
  if (region == "All Regions") {
    filtered_data <- data %>% filter(Age >= min_age, Age <= max_age)
  } else {
    filtered_data <- data %>% filter(Age >= min_age, Age <= max_age, Region == region)
  }
  
  ggplot(filtered_data, aes_string(x = "Age", y = activity, color = "Region")) +
    geom_point(alpha = 0.6) +
    labs(
      title = paste("Time Spent on", gsub("([a-z])([A-Z])", "\\1 \\2", activity), "by Age"),
      x = "Age",
      y = "Hours"
    ) +
    theme_minimal() +
    scale_color_brewer(palette = "Dark2")
}

# Run the Shiny app
shinyApp(ui = ui, server = server)
