<div class="tagidsUsers index">
	<h2><?php echo __('Associações Tag/Usuário'); ?></h2>
	<table cellpadding="0" cellspacing="0">
	<thead>
	<tr>
			<th><?php echo $this->Paginator->sort('id'); ?></th>
			<th><?php echo $this->Paginator->sort('tagid_id'); ?></th>
			<th><?php echo $this->Paginator->sort('user_id'); ?></th>
			<th><?php echo $this->Paginator->sort('created'); ?></th>
			<th><?php echo $this->Paginator->sort('modified'); ?></th>
			<th class="actions"><?php echo __('Actions'); ?></th>
	</tr>
	</thead>
	<tbody>
	<?php foreach ($tagidsUsers as $tagidsUser): ?>
	<tr>
		<td><?php echo h($tagidsUser['TagidsUser']['id']); ?>&nbsp;</td>
		<td>
			<?php echo $this->Html->link($tagidsUser['Tagid']['id'], array('controller' => 'tagids', 'action' => 'view', $tagidsUser['Tagid']['id'])); ?>
		</td>
		<td>
			<?php echo $this->Html->link($tagidsUser['User']['id'], array('controller' => 'users', 'action' => 'view', $tagidsUser['User']['id'])); ?>
		</td>
		<td><?php echo h($tagidsUser['TagidsUser']['created']); ?>&nbsp;</td>
		<td><?php echo h($tagidsUser['TagidsUser']['modified']); ?>&nbsp;</td>
		<td class="actions">
			<?php echo $this->Html->link(__('View'), array('action' => 'view', $tagidsUser['TagidsUser']['id'])); ?>
			<?php echo $this->Html->link(__('Edit'), array('action' => 'edit', $tagidsUser['TagidsUser']['id'])); ?>
			<?php echo $this->Form->postLink(__('Delete'), array('action' => 'delete', $tagidsUser['TagidsUser']['id']), array(), __('Are you sure you want to delete # %s?', $tagidsUser['TagidsUser']['id'])); ?>
		</td>
	</tr>
<?php endforeach; ?>
	</tbody>
	</table>
	<p>
	<?php
	echo $this->Paginator->counter(array(
	'format' => __('Page {:page} of {:pages}, showing {:current} records out of {:count} total, starting on record {:start}, ending on {:end}')
	));
	?>	</p>
	<div class="paging">
	<?php
		echo $this->Paginator->prev('< ' . __('previous'), array(), null, array('class' => 'prev disabled'));
		echo $this->Paginator->numbers(array('separator' => ''));
		echo $this->Paginator->next(__('next') . ' >', array(), null, array('class' => 'next disabled'));
	?>
	</div>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Associar Usuário/Tag'), array('action' => 'add')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Tags'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Listar Usuários'), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Adicionar usuário'), array('controller' => 'users', 'action' => 'add')); ?> </li>
	</ul>
</div>
