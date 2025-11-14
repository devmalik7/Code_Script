import javax.swing.*;
import javax.swing.border.LineBorder;

import java.awt.*;

public class RandomQuoteGenerator {

    private String[] quotes = {
        "Life isn’t about getting and having, it’s about giving and being. - Kevin Kruse",
        "Whatever the mind of man can conceive and believe, it can achieve. - Napoleon Hill",
        "The only way to do great work is to love what you do. - Steve Jobs"
    };

    public String getRandomQuote() {
        int randomIndex = (int) (Math.random() * quotes.length);
        return quotes[randomIndex];
    }

    public static void main(String[] args) {
        RandomQuoteGenerator generator = new RandomQuoteGenerator();

        // Create JFrame
        JFrame frame = new JFrame("Seep");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1920, 1080);
        frame.setResizable(false);
        frame.setLayout(new BorderLayout());

        // Load image
        ImageIcon image = new ImageIcon("Seep.png");
        JLabel imageLabel = new JLabel(image);
        imageLabel.setHorizontalAlignment(JLabel.CENTER);
        imageLabel.setVerticalAlignment(JLabel.CENTER);
        imageLabel.setLayout(new BorderLayout()); // enable overlay of quote

        // Quote label (white text on black background)
        JLabel quoteLabel = new JLabel(generator.getRandomQuote(), SwingConstants.CENTER);
        quoteLabel.setFont(new Font("Arial", Font.BOLD, 16));
        quoteLabel.setForeground(Color.WHITE);
        quoteLabel.setBackground(Color.BLACK);
        quoteLabel.setOpaque(true);
        quoteLabel.setHorizontalAlignment(SwingConstants.CENTER);
        quoteLabel.setVerticalAlignment(SwingConstants.CENTER);

        // Overlay quote on image
        imageLabel.add(quoteLabel, BorderLayout.CENTER);

        // Create top panel for two buttons
        JPanel topPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 10, 10));
        topPanel.setOpaque(true);
        topPanel.setBackground(Color.BLACK);  // transparent so image shows behind

        JButton button1 = new JButton("Fetch  Quote from API");
        button1.setFont(new Font("Arial", Font.PLAIN, 16));
        button1.setBackground(new Color(30, 30, 30));
        button1.setForeground(Color.WHITE);
        button1.setFocusPainted(false);

        JButton fullscreenbutton = new JButton("Fullscreen");
        fullscreenbutton.setFont(new Font("Arial", Font.PLAIN, 16));
        fullscreenbutton.setBackground(new Color(30, 30, 30));
        fullscreenbutton.setForeground(Color.WHITE);
        fullscreenbutton.setFocusPainted(false);

        GraphicsDevice device = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();

        boolean[] isFullScreen = {false}; // use array to allow modification in lambda

        fullscreenbutton.addActionListener(e -> {
            if (!isFullScreen[0]) {
            frame.dispose();
            frame.setUndecorated(true);
            device.setFullScreenWindow(frame);
            frame.setVisible(true);
            isFullScreen[0] = true;
            } else {
            device.setFullScreenWindow(null);
            frame.dispose();
            frame.setUndecorated(false);
            frame.setExtendedState(JFrame.NORMAL);
            frame.setSize(1920, 1080);
            frame.setVisible(true);
            isFullScreen[0] = false;
            }
        });


        topPanel.add(button1);
        topPanel.add(fullscreenbutton);

        // Create bottom "New Quote" button
        JButton newQuoteButton = new JButton("New Quote");
        newQuoteButton.setFont(new Font("Arial", Font.PLAIN, 18));
        newQuoteButton.setFocusPainted(false);
        newQuoteButton.setBackground(new Color(30, 30, 30)); // dark gray
        newQuoteButton.setForeground(Color.WHITE);
        newQuoteButton.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));
        newQuoteButton.setPreferredSize(new Dimension(200, 60));
        newQuoteButton.addActionListener(e -> quoteLabel.setText(generator.getRandomQuote()));

        // Main panel to hold image + bottom button
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(imageLabel, BorderLayout.CENTER);
        mainPanel.add(newQuoteButton, BorderLayout.SOUTH);

        // Add panels to frame
        frame.add(topPanel, BorderLayout.NORTH);
        frame.add(mainPanel, BorderLayout.CENTER);

        // Show window
        frame.setVisible(true);

        // Auto-update quote every 5 seconds
        new Timer(5000, e -> quoteLabel.setText(generator.getRandomQuote())).start();
        // Make button1 disappear after 5 seconds
        Timer hideTimer = new Timer(5000, e -> button1.setVisible(false));
        hideTimer.setRepeats(false); // only hide once
        hideTimer.start();

        // Make button1 visible again when the mouse moves
        frame.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
        @Override
        public void mouseMoved(java.awt.event.MouseEvent e) {
        button1.setVisible(true);
        // Restart the hide timer
        hideTimer.restart();
        }
        });

        Timer hideTimer2 = new Timer(5000, e -> fullscreenbutton.setVisible(false));
        hideTimer2.setRepeats(false); // only hide once
        hideTimer2.start();

        frame.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
        @Override
        public void mouseMoved(java.awt.event.MouseEvent e) {
        fullscreenbutton.setVisible(true);
        // Restart the hide timer
        hideTimer2.restart();
        }
        });


    }
}
