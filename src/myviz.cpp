
#include "myviz/myviz.hpp"

MyViz::MyViz(rviz_common::VisualizationFrame* frame,
         rviz_common::ros_integration::RosNodeAbstractionIface::WeakPtr ros_node_abs,
         QWidget* parent )
  : QMainWindow( parent )
  , frame_(frame)
  , ros_node_abs_(ros_node_abs)
{
    QLabel* thickness_label = new QLabel( "Line Thickness" );
    QSlider* thickness_slider = new QSlider( Qt::Horizontal );
    thickness_slider->setMinimum( 1 );
    thickness_slider->setMaximum( 100 );
    QLabel* cell_size_label = new QLabel( "Cell Size" );
    QSlider* cell_size_slider = new QSlider( Qt::Horizontal );
    cell_size_slider->setMinimum( 1 );
    cell_size_slider->setMaximum( 100 );
    QGridLayout* controls_layout = new QGridLayout();
    controls_layout->addWidget( thickness_label, 0, 0 );
    controls_layout->addWidget( thickness_slider, 0, 1 );
    controls_layout->addWidget( cell_size_label, 1, 0 );
    controls_layout->addWidget( cell_size_slider, 1, 1 );

    std::cout << "Hola que tal 0.25" << std::endl;

    // Set Layout of Render Panel
    main_layout = new QVBoxLayout;
    main_layout->addLayout( controls_layout );
    std::cout << "Hola que tal 0.5" << std::endl;

    QWidget * central_widget = new QWidget(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);

    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);

    // connect( thickness_slider, SIGNAL( valueChanged( int )), this, SLOT( setThickness( int )));
    // connect( cell_size_slider, SIGNAL( valueChanged( int )), this, SLOT( setCellSize( int )));

    std::cout << "Hola que tal 0.75" << std::endl;

    thickness_slider->setValue( 25 );
    cell_size_slider->setValue( 10 );
    std::cout << "Hola que tal 1" << std::endl;
}

MyViz::~MyViz()
{
    delete frame_;
}

void MyViz::setApp(QApplication * app){
    frame_->setApp(app);
    frame_->initialize(ros_node_abs_, "");
    
    // With the frame initialize, the rest of the Window can be initialized too
    initialize();

}

void MyViz::initialize(){
    // Initialize the Rviz2
    rviz_common::RenderPanel* render_panel_;
    // render_panel_ = new rviz_common::RenderPanel();
    // render_panel_->getRenderWindow()->initialize();

    // Get the useful
    manager_ = frame_->getManager();
    render_panel_ = frame_->getRenderPanel();
    
    // Display the Grid
    grid_ = manager_->createDisplay("rviz/Grid", "adjustable grid", true);
    assert( grid_ != NULL );
    grid_->subProp( "Line Style" )->setValue( "Billboards" );    //This doesnt work
    grid_->subProp( "Color" )->setValue( QColor( Qt::yellow ) ); //This doesnt work

    // Add to visualization
    main_layout->addWidget( render_panel_ );
}

// Slots
void MyViz::setThickness( int thickness_percent ) {
    if( grid_ != NULL ) {
        grid_->subProp( "Line Style" )->subProp( "Line Width" )->setValue( thickness_percent / 100.0f );
    }
}

void MyViz::setCellSize( int cell_size_percent ) {
    if( grid_ != NULL ) {
        grid_->subProp( "Cell Size" )->setValue( cell_size_percent / 10.0f );
    }
}