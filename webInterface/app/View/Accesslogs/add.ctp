<div class="accesslogs form">
<?php echo $this->Form->create('Accesslog'); ?>
	<fieldset>
		<legend><?php echo __('Add Accesslog'); ?></legend>
	<?php
		echo $this->Form->input('tagid_id');
		echo $this->Form->input('user_id');
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit')); ?>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>

		<li><?php echo $this->Html->link(__('List Accesslogs'), array('action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('List Tagids'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('New Tagid'), array('controller' => 'tagids', 'action' => 'add')); ?> </li>
		<li><?php echo $this->Html->link(__('List Users'), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('New User'), array('controller' => 'users', 'action' => 'add')); ?> </li>
	</ul>
</div>
